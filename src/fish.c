#include "fish.h"

//static bool fishright = true;

float prevx = 0, prevy = 0, prevz = 0;

fish_t fish_create(uint8_t variant, rspq_block_t *dpl) {
	//float randScale = (rand() % 100) / 3000.0f + 0.03f;
	float basex = -20.f, basey = 15.f, basez = 0;
	float posx = 0, posy = 0, posz = 0;

	
	float spawn_threshold = 5.0f;
	// if (id == 1) {

	srand(getentropy32());
	float randOffsetx = (rand() % 100) / 3000.0f + 0.03f;
	srand(getentropy32() * 2);
	float randOffsetz = (rand() % 100) / 30.0f + 0.13f;
	//srand(getentropy32());
	srand(getentropy32() + 922);
	float randOffsety = (rand() % 100) / 3.0f + 1.13f;
	
	

	posx = basex + randOffsetx;
	posz = basez + randOffsetz;
	posy = basey + randOffsety;

	// float magnitude = sqrtf(posx + posy + posz)

	// if(magnitude > spawn_threshold) {

	// }

	prevx = posx;
	prevy = posy;
	prevz = posz;

	//// fish quad test?
	// posx = -10.f;
	// posy=10.f;
	// 	posz=5.f;
	// } 
	// else if(id == 1){
	// 	posz=-10.f;
	// }

	//generate random tiny offset?

	// Actor actor = (Actor){
	// 	.id = id,
	// 	.pos = {posx,posy,posz},
	// 	.rot = {0,0,0},
	// 	.scale = {1, 1, 1},
	// 	.dpl = dpl,
	// 	.modelMat = malloc_uncached(sizeof(T3DMat4FP) * FB_COUNT)
	// };

	fish_t fish = (fish_t){
		.variant = variant,
		.isMature = false,
		.isMerging = false,
		.fishLeft = true,
		.actor.pos = {posx, posy,posz},
		.actor.rot = {0,0,0},
		.actor.scale = {1,1,1},
		.actor.dpl = dpl,
		.actor.modelMat = malloc_uncached(sizeof(T3DMat4FP) * FB_COUNT)
	};

	return fish;
}

void fish_update(fish_t *fish, float delta) {

	srand(getentropy32() + frameIdx);
	float minoffset = (rand() % 100) / 300.0f + 0.03f;
	float speed = FISH_SPEED + minoffset;

	if (fish->fishLeft) {
		
		fish->actor.pos[2] += speed * delta;
	} else {
		fish->actor.rot[1] = PI;
		fish->actor.pos[2] -= speed * delta;
	}


	if (fish->actor.pos[1] > TANK_BOUNDS_Y) {
		fish->actor.pos[1] = TANK_BOUNDS_Y;
	} else if (fish->actor.pos[1] < 0.f) {
		fish->actor.pos[1] = 0.f;
	} 

	if (fish->actor.pos[2] > TANK_BOUNDS_X) {
		fish->actor.pos[2] = TANK_BOUNDS_X;
		fish->fishLeft = false;
	} else if (fish->actor.pos[2] < -TANK_BOUNDS_X) {
		fish->actor.pos[2] = -TANK_BOUNDS_X;
		fish->fishLeft = true;
	}
	

	t3d_mat4fp_from_srt_euler(&fish->actor.modelMat[frameIdx], fish->actor.scale, fish->actor.rot, fish->actor.pos);

	//return;
}

void fish_draw(fish_t *fish) {
	t3d_matrix_set(&fish->actor.modelMat[frameIdx], true);
	rspq_block_run(fish->actor.dpl);
}

void fish_delete(fish_t *fish) {
	free_uncached(fish->actor.modelMat);
}