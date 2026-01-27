#ifndef __UILIB_H
#define __UILIB_H

#include <libdragon.h>
#include <stdbool.h>
//#include "actor2d.h"

//and what abt font

typedef struct button_s {
	//sprite_t *sprite;
	float x;
	float y;
	float width;
	float height;
	char* text;

	bool visible;
} button_t;

typedef struct gui_element_s {
	sprite_t *sprite;
	float x;
	float y;
	float x_scale;
	float y_scale;
	char* text;
	float text_offs_x;
	float text_offs_y;
	float angle;
	bool visible;
} gui_element_t;

typedef struct tex_button_s {
	sprite_t *sprite;
	float x;
	float y;
	float x_scale;
	float y_scale;
	//actor2d_t s_actor; //todo swap these when i have energy?
	float width;
	float height;
	char* text;
	float text_offs_x;
	float text_offs_y;
	float angle;
	bool visible;

	// maybe a pointer to an input function?? activated on a press, dependant on hand pointer position && radius
} tex_button_t;

// typedef struct button_class_s {
// 	size_t inst_size;
// } button_class_t;
gui_element_t new_gui_thing(sprite_t *sprite, float posx, float posy, float scale, char* text, float text_offs_x, float text_offs_y);
//gui_update probly
button_t new_button(float x, float y, float width, float height, char* text);
tex_button_t new_tex_button(sprite_t *sprite, float x, float y, float scale, float width, float height, char* text, float text_offs_x, float text_offs_y);
void draw_tex_button(tex_button_t *texbutt);
void draw_gui_thing(gui_element_t *guithing);

#endif