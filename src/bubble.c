#include "bubble.h"

bubble_actor_t create_bubble_wand(rspq_block_t *dpl) {

	bubble_actor_t bubl = (bubble_actor_t){
		.speed = .0102f,
		.radius = 16.f,
		.actor.pos = {-25.f, 10.f, 0.f},
		.actor.rot = {0,0,0},
		.actor.scale = {1,1,1},
		.actor.dpl = dpl,
		.actor.modelMat = malloc_uncached(sizeof(T3DMat4FP) * FB_COUNT)
	};

	return bubl;
}

void bubble_update(bubble_actor_t *bubba, joypad_inputs_t pad) {
	// uh basically, reference pointer logic.... pass joypad??
	//bubble_actor_t *this = (bubble_actor_t)

	//STICK
	bubba->actor.pos[2] -= pad.stick_x * bubba->speed;
	bubba->actor.pos[1] += pad.stick_y * bubba->speed;

	//? clamp positions
	if (bubba->actor.pos[2] > BUBL_BOUNDS_Z) {
		bubba->actor.pos[2] = BUBL_BOUNDS_Z;
	} else if (bubba->actor.pos[2] < -BUBL_BOUNDS_Z) {
		bubba->actor.pos[2] = -BUBL_BOUNDS_Z;
	}
	

	if (bubba->actor.pos[1] > BUBL_BOUNDS_Y) {
		bubba->actor.pos[1] = BUBL_BOUNDS_Y;
	} else if (bubba->actor.pos[1] < BUBLE_BOUNDS_Y_LOW) {
		bubba->actor.pos[1] = BUBLE_BOUNDS_Y_LOW;
	}


	t3d_mat4fp_from_srt_euler(&bubba->actor.modelMat[frameIdx], bubba->actor.scale, bubba->actor.rot, bubba->actor.pos);
}

void bubble_draw(bubble_actor_t *bubl) {
	t3d_matrix_set(&bubl->actor.modelMat[frameIdx], true);
	rspq_block_run(bubl->actor.dpl);
}