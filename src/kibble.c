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



void food_update(kibble_t *food, float delta) {
	// we r going to continuously spin and fall down, until a barrier or being eaten sets us to the default OOB position. there will be 3 food in an array, juggled (possibly this can be done for fish? only process active fish?)
}


void food_draw(kibble_t *food) {
	t3d_matrix_set(&food->actor.modelMat[frameIdx], true);
	rspq_block_run(food->actor.dpl);
}


// void food_delete(kibble_t *food) {

// }