#ifndef __FISH_H
#define __FISH_H

//#include "actor2d.h"
//#include <stdlib.h>
#include "global.h"
#include "actor.h"
#include "kibble.h"
#include <stdbool.h>

#define MAX_FISH 255U

#define TANK_BOUNDS_X 12.0f
#define TANK_BOUNDS_Y 16.0f

#define FISH_SPEED 2.0f

#define PI 3.14159f

typedef enum {REGULAR = 0, HUNGRY = 1, SMOOCH = 2} FishState_t;

typedef struct fish_s {
	Actor actor;
	//actor2d_t actor;
	// no actor2d fuck it
	//float zdepth;
	uint8_t variant;
	//uint16_t pseed;
	//hunger?
	bool isMature;
	bool isMerging;

	T3DVec3 direction;

	bool fishLeft;
	bool isDead;
	bool active;

	FishState_t fstate;

	uint32_t lifetime;
	uint32_t starvetime;

} fish_t;

//int find_free_fish(fish_t *fisharray);
void fish_append(fish_t *fishes, rspq_block_t *dpl, playerstats_t *p1);
void fish_cull(fish_t *fishies);


fish_t fish_create(uint8_t variant, rspq_block_t *dpl, uint8_t index, bool active);
void fish_update(fish_t *fish, float delta, kibble_t *food_storage);
void fish_draw(fish_t *fish);
void fish_delete(fish_t *fish);

#endif