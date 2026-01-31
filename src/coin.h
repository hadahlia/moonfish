#ifndef __COIN_H
#define __COIN_H

//? uh this could be an overlay??? (nah idk)

#include "actor.h"

typedef struct coin_s {
	Actor actor;

} coin_t;

coin_t coin_create(rspq_block_t *dpl, float y, float z);
void coin_update(coin_t *coin);
void coin_draw(coin_t *coin);
void coin_delete(coin_t *coin);

#endif