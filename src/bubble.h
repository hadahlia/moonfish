#ifndef __BUBBLE_H
#define __BUBBLE_H

#include "actor.h"

#define BUBL_BOUNDS_Z 16.0f
#define BUBL_BOUNDS_Y 22.0f
#define BUBLE_BOUNDS_Y_LOW -2.f

typedef struct bubble_actor_s {
	Actor actor;
	float speed;
	float radius;
	//use the pointer's radius? or. hm
} bubble_actor_t;

bubble_actor_t create_bubble_wand(rspq_block_t *dpl);
void bubble_update(bubble_actor_t *bubba, joypad_inputs_t pad);
void bubble_draw(bubble_actor_t *bubl);

#endif