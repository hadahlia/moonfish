#include "fish.h"


//static bool fishright = true;

wav64_t wavfish;

// float prevx = 0, prevy = 0, prevz = 0;


static inline int find_free_fish(fish_t *fisharray) {

	for(int i=0; i<MAX_FISH; i++) {
		if(fisharray[i].active == false) {
			return i;
		}
	}

	return -1;
}

void fish_append(fish_t *fishes, rspq_block_t *dpl, playerstats_t *p1, int fishId) {
	int slot = find_free_fish(fishes);
	//int slot = p1->fishCount;
	// if(slot==-1) {
	// 	return;
	// }
	//fish_create?
	fishes[slot] = fish_create(fishId, dpl, slot, true);

	// fishes[slot] = (fish_t){
	// 	.variant = fishId,
	// 	//.pseed = srand(getentropy32),
	// 	.isMature = false,
	// 	.isMerging = false,
	// 	.mergeNow = false,
	// 	.smoochTarget = -1,
	// 	.direction = {{0, 0, 1}},
	// 	.fishLeft = true,
	// 	.isDead = false,
	// 	.active = true,
	// 	.sound_played = false,
	// 	.fstate = REGULAR,
	// 	.lifetime = 0,
	// 	.starvetime = 500,
	// 	//.actor.pos = {posx, posy,posz},
	// 	.actor.rot = {0,0,0},
	// 	.actor.scale = {0.5,0.5,0.5},
	// 	.actor.dpl = dpl
	// };

	//p1->fishCount +=1;
	p1->fishCount = slot + 1;
}


void fish_cull(fish_t *fishies) {
	int final_id = 0;
	for(uint8_t i = 0; i<MAX_FISH; ++i) {
		if(fishies[i].isDead == false) continue;
		//if(fishies[i+1].active == true) {
			//fishies[i] = fishies[i+1];
		
		//}
		fishies[i].active = false;
		//fish_delete(&fishies[i]);
		final_id = i;
		// for(uint8_t f = i; f<MAX_FISH; ++i) {
			
			
		// }
		
	}
	//if(final_id > 0 && fishies[final_id].active == true) fishies[final_id].active = false;
}


fish_t fish_create(uint8_t variant, rspq_block_t *dpl, uint8_t index, bool active) {
	//float randScale = (rand() % 100) / 3000.0f + 0.03f;
	//float basex = -20.f, basey = 15.f, basez = 0;
	T3DVec3 spawnv = {{-22.f, 10.f, 0.f}};

	// uh whats the idea here. spawn vector, normalized. i take random offset from -1 to 1, multiply it by tank_bounds/2, and multiply that by the normalized spawn vector


	float posx = 0, posy = 0, posz = 0;

	
	//float spawn_threshold = 5.0f;
	// if (id == 1) {

	//srand(getentropy32());
	//float randOffsetx = (rand() % 100) / 3000.0f + 0.03f;
	float offsetX = index * 0.05f;
	
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

	//float 

	fish_t fish = (fish_t){
		.variant = variant,
		//.pseed = srand(getentropy32),
		.isMature = false,
		.isMerging = false,
		.mergeNow = false,
		.smoochTarget = -1,
		.direction = {{0, 0, 1}},
		.fishLeft = true,
		.isDead = false,
		.active = active,
		.sound_played = false,
		.fstate = REGULAR,
		.lifetime = 0,
		.starvetime = 500,
		.actor.pos = {posx, posy,posz},
		.actor.rot = {0,0,0},
		.actor.scale = {0.5,0.5,0.5},
		.actor.dpl = dpl,
		.actor.modelMat = malloc_uncached(sizeof(T3DMat4FP) * FB_COUNT)
	};

	return fish;
}

void fish_smooch(fish_t *fish,fish_t *fishes) {

	int merge1 = -1, merge2 = -1;
	//todo um

	for(uint8_t i = 0; i<MAX_FISH; ++i) {
		if(fishes[i].active == true && fishes[i].isMature == true) {
			//?set that fish smooch target
			//if(fishies[i].isMerging == true) continue;

			fishes[i].isMerging = true;
			
			merge1= i;

			for(uint8_t f = i+1; f<MAX_FISH; ++f) {
				if(fishes[f].active == true && fishes[f].isMature == true) {
					//?set the second smooch target yoooo
					fishes[f].isMerging = true;
					merge2 = f;
				}
			}

			fishes[merge1].smoochTarget = merge2;
			fishes[merge2].smoochTarget = merge1;
		}
	}

	// if(merge1 != -1 && merge2 != -1) {
		
	// }
}

void fish_update(fish_t *fish, float delta, kibble_t *food_storage, fish_t *all_fish, playerstats_t *p1) {
	if(fish->active == false) return;
	if(fish->isDead == true) {
		fish->actor.rot[0] = PI;
		fish->actor.pos[1] += delta;
		if(fish->sound_played == false) {
			play_sound(&wavfish, "rom:/fish_die.wav64", 3);
			fish->sound_played = true;
		}
		

		if (fish->actor.pos[1] > TANK_BOUNDS_Y) {
			fish->actor.pos[1] = TANK_BOUNDS_Y;
		} else if (fish->actor.pos[1] < 4.f) {
			fish->actor.pos[1] = 4.f;
		} 

		t3d_mat4fp_from_srt_euler(&fish->actor.modelMat[frameIdx], fish->actor.scale, fish->actor.rot, fish->actor.pos);
		return;
	} 

	if(fish->isMerging == true) {fish->fstate = SMOOCH;} else if(fish->isMature) {
		fish_smooch(fish, all_fish);
	}
	
	if(fish->starvetime > 0) {
		fish->starvetime -= 1;

		
	}

	
	if(fish->starvetime == 0) {
		fish->isDead = true;
		fish->sound_played = false;
		return;
	} else if(fish->starvetime < 360 ) {
		if(fish->sound_played == false) {
			if(!mixer_ch_playing(2)) play_sound(&wavfish, "rom:/warning.wav64", 3);
			fish->sound_played = true;
		}
		if(food_storage[0].active == true || food_storage[1].active == true || food_storage[2].active == true) {
			fish->fstate = HUNGRY;
			
		}
		//fish->isDead = true;
		
	} else if(fish->isMature == false) {
		fish->lifetime += 1;
		float scale_coeff = fish->lifetime * 0.001f;

		if(scale_coeff >0.5f) {
			fish->actor.scale[0] = scale_coeff;
			fish->actor.scale[1] = scale_coeff;
			fish->actor.scale[2] = scale_coeff;
		}
		

		if(fish->lifetime > 1600) {
			fish->isMature = true;
			fish->actor.scale[0] = 1.8f;
			fish->actor.scale[1] = 1.8f;
			fish->actor.scale[2] = 1.8f;

			// coin_spawn(fish->actor.pos[1], fish->actor.pos[2]);
			// coin_spawn(fish->actor.pos[1] + 1, fish->actor.pos[2] + 1);

			p1->money += 50;
		}
	}
	
	srand(frameIdx);
	float minoffset = 1.0f * (rand() / 2) / FISH_SPEED + 0.03f;
	float speedOffset = (2.0f * (rand() % 100) / 100.0f) ;
	float speed = FISH_SPEED * speedOffset / fish->actor.scale[0];

	if (fish->fishLeft) {
		fish->actor.rot[1] = 0;
	} else {
		fish->actor.rot[1] = PI;
	}

	if(fish->fstate == REGULAR) {
		//? IDLE ESSENTIALLY

		

		if (fish->fishLeft) {
			//fish->actor.rot[1] = 0;
			//t3d_vec3_lerp()
			fish->actor.pos[2] +=  speed * delta;
		} else {
			
			fish->actor.pos[2] -= speed * delta;
		}


		

		
	
	} else if(fish->fstate == HUNGRY) {
		if(food_storage[0].active == false && food_storage[1].active == false && food_storage[2].active == false) {
			//welp. regular 
			fish->fstate = REGULAR;
			return;
		}

		T3DVec3 fishpos = {{0,fish->actor.pos[1], fish->actor.pos[2] }};

		
		T3DVec3 foodpos0 = {{0, 999, 999}};
		T3DVec3 foodpos1 = {{0, 999, 999}};
		T3DVec3 foodpos2 = {{0, 999, 999}};

		if (food_storage[0].active == true) {
			//foodpos0.v = {0, food_storage[0].actor.pos[1], food_storage[0].actor.pos[2]};
			foodpos0.x = 0;
			foodpos0.y = food_storage[0].actor.pos[1];
			foodpos0.z = food_storage[0].actor.pos[2];
			
		}

		if (food_storage[1].active == true) {
			//foodpos1.v = {0, food_storage[1].actor.pos[1], food_storage[1].actor.pos[2]};

			foodpos1.x = 0;
			foodpos1.y = food_storage[1].actor.pos[1];
			foodpos1.z = food_storage[1].actor.pos[2];
		} 

		if (food_storage[2].active == true) {
			//foodpos2.v = {0, food_storage[2].actor.pos[1], food_storage[2].actor.pos[2]};

			foodpos2.x = 0;
			foodpos2.y = food_storage[2].actor.pos[1];
			foodpos2.z = food_storage[2].actor.pos[2];
		} 

		
		
		
		T3DVec3 ra, rb, rc;

		t3d_vec3_diff(&ra, &foodpos0, &fishpos);
		t3d_vec3_diff(&rb, &foodpos1, &fishpos);
		t3d_vec3_diff(&rc, &foodpos2, &fishpos);

		//t3d_vec3

		float lena = t3d_vec3_len(&ra);
		float lenb = t3d_vec3_len(&rb);
		float lenc = t3d_vec3_len(&rc);
		uint8_t id = -1;
		//float shortest = 0.f;
		T3DVec3 target = {{0, 0, 0}};
		if(lena < lenb) {
			if(lenb < lenc) {
				//lena smallest
				//shortest = lena;
				id = 0;
				target = foodpos0;
			} else {
				//lenc smallest
				id = 2;
				//shortest = lenc;
				target = foodpos2;
			}
		} else if (lenb < lenc){
			//lenb smallest
			//shortest = lenb;
			id = 1;
			target = foodpos1;
		} else {
			//lenc smallest
			//shortest = lenc;
			id = 2;
			target = foodpos2;
		}
		if(t3d_vec3_distance(&target, &fishpos) > 85.f) {
			fish->fstate = REGULAR;
			return;
		}
		// if() {
		// 	fish->fstate = REGULAR;
		// }
		

		T3DVec3 direction;
		t3d_vec3_diff(&direction, &target, &fishpos);
		
		if(direction.v[2] > 0 || direction.v[1] > 0) {
			t3d_vec3_norm(&direction);
		}
		

		//? do stuff to direction?

		//t3d_vec3_mul()
		//float rngdir = (2.0f * (rand() % 100) / 100.0f)

		if(direction.z < 0) {
			fish->fishLeft = false;
		} else {
			fish->fishLeft = true;
		}

		fish->actor.pos[1] += direction.y * FISH_SPEED * delta;
		fish->actor.pos[2] += direction.z * FISH_SPEED * delta;
		//T3DVec3 up = {{0, 1, 0}};

		//T3DMat4 *mat = malloc_uncached(sizeof(T3DMat4) * FB_COUNT);
		//t3d_mat4_identity(mat);

		if(t3d_vec3_distance(&target, &fishpos) < 1.f) {

			food_storage[id].active=false;
			fish->starvetime = 500;
			fish->actor.scale[0] += 0.1f;
			fish->actor.scale[1] += 0.1f;
			fish->actor.scale[2] += 0.1f;
			fish->fstate = REGULAR;
			fish->sound_played = false;

			//coin_spawn(fish->actor.pos[1], fish->actor.pos[2]);
			p1->money += 25;
			return;
		}

		//t3d_mat4_from_srt_euler(mat,  fish->actor.scale, fish->actor.rot, fish->actor.pos);

		//t3d_mat4fp_from_srt_euler(&fish->actor.modelMat[frameIdx], fish->actor.scale, fish->actor.rot, fish->actor.pos);
		// t3d_mat4_look_at(mat, &fishpos, &target, &up);

		// t3d_mat4_to_fixed(&fish->actor.modelMat[frameIdx], mat);

		

		//t3d_mat4
		// kibble_t *food = &food_storage[0];
		// for(int k=1; k<3; k++) {
		// 	if(food_storage[k].active) {
		// 		kibble_t *food = &food_storage[k];
		// 	}
			
		// }
		
		// if(!food->active) fish->fstate = REGULAR;

		// float direction_y = food->actor.pos[1] - fish->actor.pos[1];
		// float direction_z = food->actor.pos[2] - fish->actor.pos[2];

		// //t3d_vec3_norm()

		// if(direction_y > 1) {
		// 	direction_y = 1;
		// } else {
		// 	direction_y = 0;
		// }
		// if(direction_z > 1) {
		// 	direction_z = 1;
		// } else {
		// 	direction_z = 0;
		// }

		// if (direction_y != 0) {
		// 	fish->actor.pos[1] += direction_y * FISH_SPEED * delta;
		// }

		// if (direction_z != 0) {
		// 	fish->actor.pos[2] += direction_z * FISH_SPEED * delta;
		// }

		// if (direction_y && direction_z < 0.1f ) {
		// 	// eat da food
		// 	food->active=false;
		// 	fish->starvetime = 2000;
		// 	fish->fstate = REGULAR;
		// }


	} else if(fish->fstate == SMOOCH) {
		//? MERGING STATE

		if(fish->smoochTarget == -1) return;
		// for(uint8_t f=0; f<MAX_FISH; ++f) {
		// 	if(all_fish[f].isMerging == true) {

		// 	}

		// }

		//? find a second fish merging, and go to them
		T3DVec3 myPos = {{0, fish->actor.pos[1], fish->actor.pos[2]}};
		T3DVec3 target = {{0, all_fish[fish->smoochTarget].actor.pos[1], all_fish[fish->smoochTarget].actor.pos[2]}};

		T3DVec3 direction = {{0, 0, 0}};

		t3d_vec3_diff(&direction, &target, &myPos);
		t3d_vec3_norm(&direction);


		fish->actor.pos[1] += direction.y * FISH_SPEED * delta;
		fish->actor.pos[2] += direction.z * FISH_SPEED * delta;


		if(t3d_vec3_distance(&target, &myPos) < 1.f) {
			//? MERGE THE FISHHHH
			fish->mergeNow = true;
			all_fish[fish->smoochTarget].mergeNow = true;
			// fish->isDead = true;
			// all_fish[fish->smoochTarget].isDead = true;

			//fish_append()
		}

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

	t3d_mat4fp_from_srt_euler(&fish->actor.modelMat[frameIdx], fish->actor.scale, fish->actor.rot, fish->actor.pos);

	//return;
}



void fish_draw(fish_t *fish) {
	//if(fish->isDead == true) { return; }
	if(fish->active == false) return;
	t3d_matrix_set(&fish->actor.modelMat[frameIdx], true);
	rspq_block_run(fish->actor.dpl);
}

void fish_delete(fish_t *fish) {
	free_uncached(fish->actor.modelMat);
}