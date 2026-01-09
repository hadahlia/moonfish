#ifndef __ACTOR_H
#define __ACTOR_H

#include <libdragon.h>
#include <t3d/t3d.h>

#define FB_COUNT 3

static int frameIdx;

typedef struct {
	uint32_t id;
	float pos[3];
	float rot[3];
	float scale[3];

	rspq_block_t *dpl;
	T3DMat4FP *modelMat;
} Actor;

Actor actor_create(uint32_t id, rspq_block_t *dpl);
void actor_update(Actor *actor);
void actor_draw(Actor *actor);
void actor_delete(Actor *actor);

#endif