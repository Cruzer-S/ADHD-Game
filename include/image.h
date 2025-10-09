#ifndef IMAGE_H__
#define IMAGE_H__

enum image {
	IMAGE_SPACE = 0,
	IMAGE_GRASS,
	IMAGE_PLAYER,
	IMAGE_ROCK,

	IMAGE_SIZE
};

extern char img2chr[IMAGE_SIZE];

#endif
