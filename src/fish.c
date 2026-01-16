#include "fish.h"

//static bool fishright = true;



// float prevx = 0, prevy = 0, prevz = 0;




fish_t fish_create(uint8_t variant, rspq_block_t *dpl, uint8_t index) {
	//float randScale = (rand() % 100) / 3000.0f + 0.03f;
	//float basex = -20.f, basey = 15.f, basez = 0;
	T3DVec3 spawnv = {{-20.f, 10.f, 0.f}};

	// uh whats the idea here. spawn vector, normalized. i take random offset from -1 to 1, multiply it by tank_bounds/2, and multiply that by the normalized spawn vector


	float posx = 0, posy = 0, posz = 0;

	
	//float spawn_threshold = 5.0f;
	// if (id == 1) {

	//srand(getentropy32());
	//float randOffsetx = (rand() % 100) / 3000.0f + 0.03f;
	float offsetX = index * 0.1f;
	
	srand((getentropy32()) + frameIdx);
	//float randOffsety = (rand() % 100) / 3.0f + 1.13f;
	//float randOffsety = (rand() / 1) * 2.0f - 1.0f;
	float randOffsety = (2.0f * (rand() % 100) / 100.0f - 1.0f) * (TANK_BOUNDS_Y);
	//srand((getentropy32()) + frameIdx + 2);
	//float randOffsetz = (rand() % 100) / 30.0f + 0.13f;
	//float randOffsetz = 2.0f * (rand() / 2.0f) - 1.f;
	float randOffsetz = (2.0f * (rand() % 100) / 100.0f - 1.0f) * (TANK_BOUNDS_X*0.5f);
	//srand(getentropy32());
	
	
	

	posx = spawnv.v[0] + offsetX;
	posy = spawnv.v[1] + randOffsety;
	posz = spawnv.v[2] + randOffsetz;
	

	// float magnitude = sqrtf(posx + posy + posz)

	// if(magnitude > spawn_threshold) {

	// }

	// prevx = posx;
	// prevy = posy;
	// prevz = posz;

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
		.fstate = REGULAR,
		.lifetime = 0,
		.actor.pos = {posx, posy,posz},
		.actor.rot = {0,0,0},
		.actor.scale = {1,1,1},
		.actor.dpl = dpl,
		.actor.modelMat = malloc_uncached(sizeof(T3DMat4FP) * FB_COUNT)
	};

	return fish;
}

void fish_update(fish_t *fish, float delta) {

	if(fish->fstate == REGULAR) {
		srand(frameIdx);
		float minoffset = 1.0f * (rand() / 2) / FISH_SPEED + 0.03f;
		float speedOffset = (2.0f * (rand() % 100) / 100.0f);
		float speed = FISH_SPEED * speedOffset;

		if (fish->fishLeft) {
			fish->actor.rot[1] = 0;
			fish->actor.pos[2] += speed * delta;
		} else {
			fish->actor.rot[1] = PI;
			fish->actor.pos[2] -= speed * delta;
		}


		if (fish->actor.pos[1] > TANK_BOUNDS_Y) {
			fish->actor.pos[1] = TANK_BOUNDS_Y;
		} else if (fish->actor.pos[1] < 4.f) {
			fish->actor.pos[1] = 4.f;
		} 

		if (fish->actor.pos[2] > TANK_BOUNDS_X) {
			fish->actor.pos[2] = TANK_BOUNDS_X;
			fish->fishLeft = false;
		} else if (fish->actor.pos[2] < -TANK_BOUNDS_X) {
			fish->actor.pos[2] = -TANK_BOUNDS_X;
			fish->fishLeft = true;
		}
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