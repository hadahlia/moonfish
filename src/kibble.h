#ifndef __KIBBLE_H
#define __KIBBLE_H

#include "actor.h"
#include <stdbool.h>

typedef struct kibble_s {
	Actor actor;

	bool active;
} kibble_t;

void food_spawn(kibble_t *kibble, float y, float z);
kibble_t food_create(rspq_block_t *dpl);
void food_update(kibble_t *food, float delta);
void food_draw(kibble_t *food);
void food_delete(kibble_t *food);

#endif