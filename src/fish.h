#ifndef __FISH_H
#define __FISH_H

//#include "actor2d.h"
//#include <stdlib.h>
#include "actor.h"

#define MAX_FISH 255U

#define TANK_BOUNDS_X 20.0f
#define TANK_BOUNDS_Y 10.0f

#define FISH_SPEED 2.0f

#define PI 3.14159f

typedef struct fish_s {
	Actor actor;
	//actor2d_t actor;
	// no actor2d fuck it
	//float zdepth;
	uint8_t variant;
	//hunger?
	bool isMature;
	bool isMerging;

	bool fishLeft;

} fish_t;

fish_t fish_create(uint8_t variant, rspq_block_t *dpl);
void fish_update(fish_t *fish, float delta);
void fish_draw(fish_t *fish);
void fish_delete(fish_t *fish);

#endif