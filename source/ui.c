#include <stdlib.h>
#include <stdbool.h>

#include <ncurses.h>
#include <panel.h>

#include "ui.h"

typedef struct string_list {
	int x, y;
	char *string;
	int length;
	struct string_list *next;
} *StringList;

struct ui {
	PANEL *panel;

	StringList slist;
	bool border;
};

static void print_in_box(WINDOW *win,
			 int x, int y, int w, int h,
			 const char *str, int n)
{
	int row = y, col = x;
	int printed = 0;

	for (const char *p = str; *p && row < y + h && printed < n; p++) {
		if (*p == '\n' || col >= x + w) {
			row++;
			col = x;
			if (*p == '\n')
				continue;
		}

		if (row < y + h && printed < n) {
			mvwaddch(win, row, col++, *p);
			printed++;
		}
	}
}

static void ui_draw(UI ui)
{
	WINDOW *window = panel_window(ui->panel);
	int x, y, w, h;

	getmaxyx(window, h, w);
	if (ui->border) {
		box(window, 0, 0);
		w -= 2, h -= 2;
	}

	for (StringList slist = ui->slist; slist; slist = slist->next) {
		x = slist->x, y = slist->y;
		if (ui->border)
			x++, y++;

		print_in_box(window, x, y, w, h, slist->string, slist->length);
	}
}

UI ui_create(int x, int y, int width, int height)
{
	UI ui;
	WINDOW *window;

	ui = malloc(sizeof(struct ui));
	if (ui == NULL)
		return NULL;

	window = newwin(height, width, y, x);
	ui->panel = new_panel(window);

	ui->border = true;
	ui->slist = NULL;

	ui_draw(ui);

	return ui;
}

void ui_clear(UI ui)
{
	werase(panel_window(ui->panel));
}

int ui_add_string(UI ui, int x, int y, char *string, int n)
{
	StringList slist;

	slist = malloc(sizeof(struct string_list));
	if (slist == NULL)
		return -1;

	slist->x = x;
	slist->y = y;
	slist->string = string;
	slist->length = n;
	slist->next = NULL;

	if (ui->slist)
		slist->next = ui->slist;

	ui->slist = slist;

	ui_draw(ui);

	return 0;
}

int ui_del_string(UI ui, char *string)
{
	for (StringList prev = NULL, cur = ui->slist;
			cur;
	     		prev = cur, cur = cur->next)
	{
		if (cur->string == string) {
			WINDOW *window = panel_window(ui->panel);

			if (prev)
				prev->next = cur->next;
			else
				ui->slist = NULL;

			free(cur);

			ui_clear(ui);
			ui_draw(ui);

			return 0;
		}
	}

	return -1;
}

void ui_set_border(UI ui, bool visible)
{
	if (ui->border == visible)
		return ;

	ui->border = visible;

	ui_clear(ui);
	ui_draw(ui);
}

bool ui_is_hidden(UI ui)
{
	return panel_hidden(ui->panel);
}

bool ui_is_border(UI ui)
{
	return ui->border;
}

void ui_set_hide(UI ui, bool hide)
{
	if (hide)
		hide_panel(ui->panel);
	else
		show_panel(ui->panel);
}

int ui_get_x(UI ui)
{
	return getbegx(panel_window(ui->panel));
}

int ui_get_y(UI ui)
{
	return getbegy(panel_window(ui->panel));
}

void ui_top(UI ui)
{
	top_panel(ui->panel);
}

void ui_bottom(UI ui)
{
	bottom_panel(ui->panel);
}

int ui_get_width(UI ui)
{
	return getmaxx(panel_window(ui->panel));
}

int ui_get_height(UI ui)
{
	return getmaxy(panel_window(ui->panel));
}

void ui_move(UI ui, int x, int y)
{
	move_panel(ui->panel, y, x);
}

void ui_resize(UI ui, int width, int height)
{
	WINDOW *oldwin, *tmpwin;
	int x, y;

	oldwin = panel_window(ui->panel);
	getbegyx(oldwin, y, x);

	tmpwin = newwin(height, width, y, x);

	replace_panel(ui->panel, tmpwin);
	delwin(oldwin);

	ui_draw(ui);
}

void ui_destroy(UI ui)
{
	WINDOW *window;

	window = panel_window(ui->panel);

	del_panel(ui->panel);
	delwin(window);
}
