#include "coin.h"



coin_t coins[MAX_COINS];

static inline int find_free_slot() {

	for(int i=0; i<MAX_COINS; i++) {
		if(coins[i].active == false) {
			return i;
		}
	}

	return -1;
}

void coin_spawn(float y, float z) {
	int slot = find_free_slot();
	if(slot==-1) {
		return;
	}
	coins[slot].active = true;
	coins[slot].actor.pos[1] = y;
	coins[slot].actor.pos[2] = z;
	

}

// void init_coins() {
// 	for(int c = 0; c<MAX_COINS; ++c) {
// 		coins[c] = coin_create()
// 	}
// }

coin_t coin_create(rspq_block_t *dpl, float y, float z) {

	coin_t coin = (coin_t){
		.active = true,
		.actor.pos = {-23.f, y, z},
		.actor.rot = {0,0,0},
		.actor.scale = {0.9,0.9,0.9},
		.actor.dpl = dpl,
		.actor.modelMat = malloc_uncached(sizeof(T3DMat4FP) * FB_COUNT)
	};

	return coin;
}

void coin_update(coin_t *coin, bubble_actor_t *cursor) {
	if(coin->active == false) return;
	T3DVec3 direction;

	t3d_mat4fp_from_srt_euler(&coin->actor.modelMat[frameIdx], coin->actor.scale, coin->actor.rot, coin->actor.pos);
}

void coin_draw(coin_t *coin) {
	if(coin->active == false) return;
	t3d_matrix_set(&coin->actor.modelMat[frameIdx], true);
	rspq_block_run(coin->actor.dpl);
}

void coin_delete(coin_t *coin) {
	free_uncached(coin->actor.modelMat);
}