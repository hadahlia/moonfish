#ifndef __COIN_H
#define __COIN_H

#define MAX_COINS 0xF
//? uh this could be an overlay??? (nah idk)

#include <stdbool.h>
#include "global.h"
#include "actor.h"
#include "bubble.h"



typedef struct coin_s {
	Actor actor;
	bool active;
} coin_t;

//coin_t coins[MAX_COINS];

//static inline int find_free_slot();
void coin_spawn(float y, float z);
coin_t coin_create(rspq_block_t *dpl, float y, float z);
void coin_update(coin_t *coin, bubble_actor_t *cursor);
void coin_draw(coin_t *coin);
void coin_delete(coin_t *coin);

#endif