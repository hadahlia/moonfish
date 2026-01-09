#ifndef __UILIB_H
#define __UILIB_H

#include <libdragon.h>
#include <stdbool.h>

typedef struct button_s {
	//sprite_t *sprite;
	float x;
	float y;
	float width;
	float height;
	char* text;

	bool visible;
} button_t;

typedef struct tex_button_s {
	sprite_t *sprite;
	float x;
	float y;
	float width;
	float height;
	char* text;

	bool visible;
} tex_button_t;

// typedef struct button_class_s {
// 	size_t inst_size;
// } button_class_t;

button_t new_button(float x, float y, float width, float height, char* text);
tex_button_t new_tex_button(sprite_t *sprite, float x, float y, float width, float height, char* text);

#endif