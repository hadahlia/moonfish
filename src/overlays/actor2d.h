#ifndef __ACTOR2D_H
#define __ACTOR2D_H

#include <libdragon.h>
#include <stdbool.h>

struct actor2d_s;

typedef void (*init_func_t)(struct actor2d_s *);
typedef bool (*update_func_t)(struct actor2d_s *, joypad_inputs_t);

typedef struct actor2d_s {
	void *ovl_handle;
	sprite_t *sprite;
	update_func_t update;
	float x;
	float y;
	float x_scale;
	float y_scale;
	float angle;
	bool visible;
} actor2d_t;

typedef struct actor2d_class_s {
	size_t instance_size;
	init_func_t init;
	update_func_t update;
} actor2d_class_t;

#endif