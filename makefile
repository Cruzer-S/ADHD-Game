SRC_DIR := source
OUT_DIR := output
INC_DIR := include

CC := gcc
RM := rm -rf
MKDIR := mkdir -p
CREAT := touch
ECHO := echo

PROJDB := compile_commands.json .cache

SOURCE := $(wildcard $(SRC_DIR)/*.c)
OBJECT := $(patsubst $(SRC_DIR)/%.c,$(OUT_DIR)/%.o,$(SOURCE))
DEPEND := $(patsubst $(SRC_DIR)/%.c,$(OUT_DIR)/%.d,$(SOURCE))

OUTPUT := adhd_game

.DEFAULT_GOAL = $(OUTPUT)

$(OUTPUT): $(OBJECT)
	$(CC) -o $@ $^

$(OBJECT): $(OUT_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -o $@ -c $< -I $(INC_DIR)/

$(DEPEND): $(OUT_DIR)/%.d: $(SRC_DIR)/%.c
	$(CC) -c $< -I $(INC_DIR)/ -MG -MM > $@

$(OBJECT) $(DEPEND): | $(OUT_DIR)
$(OUT_DIR):
	$(MKDIR) $@

.PHONY: all
all: $(OUTPUT)

.PHONY: clean
clean:
	$(RM) $(OUT_DIR)/
	$(RM) $(OUTPUT)

.PHONY: gitignore
gitignore:
	$(RM) .$@
	$(CREAT) .$@

	for f in $(OUT_DIR)/ $(OUTPUT) $(PROJDB) ;	\
	do											\
		$(ECHO) $$f >> .$@ ;					\
	done

ifeq ($(filter clean,$(MAKECMDGOALS)),)
-include $(DEPEND)
endif
