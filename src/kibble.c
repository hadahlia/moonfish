#include "kibble.h"

kibble_t food_create(rspq_block_t *dpl) {

	kibble_t food = (kibble_t){
		
		.actor.pos = {-25,10,0},
		.actor.rot = {0,0,0},
		.actor.scale = {1,1,1},
		.actor.dpl = dpl,
		.actor.modelMat = malloc_uncached(sizeof(T3DMat4FP) * FB_COUNT),
		.active = false
	};

	return food;
}

void food_spawn(kibble_t *kibble, float y, float z) {
	kibble->actor.pos[1] = y;
	kibble->actor.pos[2] = z;
	kibble->active = true;
}

void food_update(kibble_t *food, float delta) {
	if(!food->active) return;
	float speed = 2.f;
	float spin_speed = 2.f;
	// we r going to continuously spin and fall down, until a barrier or being eaten sets us to the default OOB position. there will be 3 food in an array, juggled (possibly this can be done for fish? only process active fish?)
	food->actor.pos[1] -= speed * delta;
	food->actor.rot[2] += spin_speed * delta;
	if(food->actor.pos[1] < -2.f) {
		food->active = false;
	}

	t3d_mat4fp_from_srt_euler(&food->actor.modelMat[frameIdx], food->actor.scale, food->actor.rot, food->actor.pos);

}


void food_draw(kibble_t *food) {
	if(!food->active) return;
	t3d_matrix_set(&food->actor.modelMat[frameIdx], true);
	rspq_block_run(food->actor.dpl);
}


// void food_delete(kibble_t *food) {

// }