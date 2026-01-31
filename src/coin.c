#include "coin.h"

coin_t coin_create(rspq_block_t *dpl, float y, float z) {

	coin_t coin = (coin_t){
		.actor.pos = {-24.5f, y, z},
		.actor.rot = {0,0,0},
		.actor.scale = {0.9,0.9,0.9},
		.actor.dpl = dpl,
		.actor.modelMat = malloc_uncached(sizeof(T3DMat4FP) * FB_COUNT)
	};

	return coin;
}

void coin_update(coin_t *coin) {

}

void coin_draw(coin_t *coin) {
	t3d_matrix_set(&coin->actor.modelMat[frameIdx], true);
	rspq_block_run(coin->actor.dpl);
}

void coin_delete(coin_t *coin) {
	free_uncached(coin->actor.modelMat);
}