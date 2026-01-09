#include "actor.h"

static int frameIdx = 0;

Actor actor_create(uint32_t id, rspq_block_t *dpl) {
	//float randScale = (rand() % 100) / 3000.0f + 0.03f;
	float posx = 0, posy = 0, posz = 0;
	if (id == 1) {
		// fish quad test?
		posx = -10.f;
		posy=10.f;
		posz=5.f;
	} 
	// else if(id == 1){
	// 	posz=-10.f;
	// }

	Actor actor = (Actor){
		.id = id,
		.pos = {posx,posy,posz},
		.rot = {0,0,0},
		.scale = {1, 1, 1},
		.dpl = dpl,
		.modelMat = malloc_uncached(sizeof(T3DMat4FP) * FB_COUNT)
	};

	return actor;
}

void actor_update(Actor *actor) {
	// actor->pos[0] = 0;
	// actor->pos[1] = 0;
	// actor->pos[2] = 0;

	// float randRot = (float)fm_fmodf(actor->id * 123.1f, 5.0f);
	// float randDist = (float)fm_fmodf(actor->id * 4645.987f, 30.5f) + 10.0f;

	// actor->rot[0] = fm_fmodf(randRot + objTime * 1.05f, RAD_360);
	// actor->rot[1] = fm_fmodf(randRot + objTime * 1.03f, RAD_360);
	// actor->rot[2] = fm_fmodf(randRot + objTime * 1.2f, RAD_360);

	// actor->pos[0] = randDist * fm_cosf(objTime * 1.6f + randDist);
	// actor->pos[1] = randDist * fm_cosf(objTime * 1.5f + randRot);
	// actor->pos[2] = randDist * fm_cosf(objTime * 1.4f + randDist*randRot);


	t3d_mat4fp_from_srt_euler(&actor->modelMat[frameIdx], actor->scale, actor->rot, actor->pos);

	//return;
}

void actor_draw(Actor *actor) {
	t3d_matrix_set(&actor->modelMat[frameIdx], true);
	rspq_block_run(actor->dpl);
}

void actor_delete(Actor *actor) {
	free_uncached(actor->modelMat);
}