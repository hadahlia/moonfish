#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include <stdlib.h>
#include <stdbool.h>
#include "actor.h"
#include "fish.h"
#include "overlays/actor2d.h"
#include "uilib.h"
//#include "util.h"

#define SHOP_BTN_NO 2u
//#define BTN_SPRITES 4u

#define MODEL_TYPE 2
#define ACTOR_COUNT 5
//#define MAX_FISH_NO 40

//#define TAU 6.28318530718f

static float objTimeLast = 0.f;
static float objTime = 0.f;
static float baseSpeed = 1.0f;
//frameIdx = 0;

typedef enum {FISH = 0, AQUA = 1, SHOP = 2, SHELF = 3} GameState_t;

//typedef enum MenuState {OFF = 0, MAIN = 1, GAME = 2}; //todo idea

//static enum GameState {FISH = 0, AQUA = 1, SHOP = 2, SHELF = 3} gstate = 1;
static GameState_t gstate = 1;

static char* state_strs[4] = { "LOUNGE?", "AQUA", "SHOP", "DEVS?"};

static bool can_switch_gs = false;



// SPRITE OVERLAY SHIT

#define MAX_SPRITES 99
#define MAX_SPRITE_TYPES 1

#define FISH_TYPES 1

// static const char* fishMats[FISH_TYPES] = { //todo nvm manual approach??
// 	"rom:/buppin.ci8.sprite",
// };

typedef struct actor2d_info_s {
	const char *name;
	const char *sprite_path;
	const char *ovl_path;
} actor2d_info_t;

static actor2d_info_t actor2d_info[MAX_SPRITE_TYPES] = {
	{"hpointer", "rom:/hand.ci8.sprite", "rom:/pointer.dso" },		// 0: hand pointer
	//{"menu", "rom:/dark.ci8.sprite", "rom:/menu.dso" }			   // 1: main menu? test square black
	// instance for coins?
};


static actor2d_t *spriteActors[MAX_SPRITES];



static int find_free_sprite_actor() {

	for(int i=0; i<MAX_SPRITES; i++) {
		if(!spriteActors[i]) {
			return i;
		}
	}

	return -1;
}

static void create_sprite_actor(int type, float x, float y) { //todo add scale params x_scale and y_scale, and angle?
	if(type < MAX_SPRITE_TYPES) {
		void *ovl_handle;
		actor2d_class_t *class;

		int slot = find_free_sprite_actor();
		if(slot==-1) {
			return;
		}

		ovl_handle = dlopen(actor2d_info[type].ovl_path, RTLD_LOCAL);
		class = dlsym(ovl_handle, "sprite_actor_class");
		assertf(class, "Failed to find actor class for %s", actor2d_info[type].name);
		spriteActors[slot] = calloc(1, class->instance_size);

		spriteActors[slot]->ovl_handle = ovl_handle;
		spriteActors[slot]->update = class->update;
		spriteActors[slot]->sprite = sprite_load(actor2d_info[type].sprite_path);
		spriteActors[slot]->x = x;
		spriteActors[slot]->y = y;
		spriteActors[slot]->x_scale = spriteActors[slot]->y_scale = 1.0f;
		spriteActors[slot]->visible = true;

		class->init(spriteActors[slot]);
	}
}

static void draw_sprite_actors() {
	rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
	for(int i=0; i<MAX_SPRITES; i++) {
		if(spriteActors[i] && spriteActors[i]->visible) {
			surface_t surf = sprite_get_pixels(spriteActors[i]->sprite);
			// rdpq_tex_blit(&surf, spriteActors[i]->x,spriteActors[i]->y, &(rdpq_blitparms_t){
			// 	.cx = surf.width/2, .cy = surf.height/2,
			// 	.scale_x = spriteActors[i]->x_scale, .scale_y = spriteActors[i]->y_scale,
			// 	.theta = spriteActors[i]->angle
			// });

			rdpq_sprite_blit(spriteActors[i]->sprite, spriteActors[i]->x,spriteActors[i]->y, /*NULL); */ &(rdpq_blitparms_t){
				.cx = surf.width/2, .cy = surf.height/2,
				.scale_x = spriteActors[i]->x_scale, .scale_y = spriteActors[i]->y_scale,
				.theta = spriteActors[i]->angle
			});

			//rdp_draw_textured_rectangle(0);
		}
	}

}

static void update_sprite_actors(joypad_inputs_t pad) {
	for(int i=0; i<MAX_SPRITES; i++) {
		if(spriteActors[i]) {
			if(!spriteActors[i]->update(spriteActors[i], pad)) {
				dlclose(spriteActors[i]->ovl_handle);
				sprite_free(spriteActors[i]->sprite);
				free(spriteActors[i]);
				spriteActors[i] = NULL;
			}
		}
	}
}


//! button inputs
// static void draw_tex_buttons() {

// }

static void btn_input(tex_button_t *texbtn, actor2d_t *spr_actor, bool *inbounds) {
	if(!texbtn->visible) return;
	float upper_x = texbtn->x + texbtn->width;
	float lower_x = texbtn->x - texbtn->width;
	float upper_y = texbtn->y + texbtn->height;
	float lower_y = texbtn->y - texbtn->height;
	if(spr_actor->y < upper_y && spr_actor->y > lower_y) {
		//you within the button y
		if(spr_actor->x < upper_x && spr_actor->x > lower_x) {
			//you ALSO within button x. YAY
			texbtn->visible = false;
			*inbounds = true;
		}

	}
}

// generic 3d actor?

// Shouldnt i just, init everything we will need? its all one room...
static void state_init(xm64player_t *xm) {
	switch(gstate) {
		case 0:
			//FISH
			
			
			break;
		case 1:
			//AQUA
			//if(mixer_ch_playing(0)) xm64player_close(xm);
			//xm64player_close(xm);
			xm64player_open(xm, "rom:/computer_fish.xm64");
			xm64player_play(xm, 0);
			
			break;
		case 2:
			//SHOP
			//if(mixer_ch_playing(0)) xm64player_close(xm);
			xm64player_open(xm, "rom:/mountain_ant_steve.xm64");
			xm64player_play(xm, 0);
			break;
		case 3:
			
			//SHELF
			//if(mixer_ch_playing(0)) xm64player_close(xm);
	}
}

//static float angle = 0.f;

void state_update(float delta, T3DVec3 *dir) {

	//angle = lerp_angle(angle, (float)gstate * (RAD_360/4.0f) + (RAD_360/4.0f), delta);

	//float vt0 = 0.f, vt1 = 0.f, vt2 = 0.f;

	T3DVec3 tDir = {{0, 0, 0}};
	
	switch(gstate) {
		case 0:
			//FISH

			tDir.v[0] = 0;
			tDir.v[1] = 0;
			tDir.v[2] = 1;
			// dir->v[0] = 0;
			// dir->v[1] = 0;
			// dir->v[2] = 1;
			break;
		case 1:
			//AQUA


			tDir.v[0] = -1;
			tDir.v[1] = 0;
			tDir.v[2] = 0;
			// dir->v[0] = -1;
			// dir->v[1] = 0;
			// dir->v[2] = 0;
			break;
		case 2:
			//SHOP
			
			tDir.v[0] = 0;
			tDir.v[1] = 0;
			tDir.v[2] = -1;
			// dir->v[0] = 0;
			// dir->v[1] = 0;
			// dir->v[2] = -1;
			break;
		case 3:
			//SHELF
			tDir.v[0] = 1;
			tDir.v[1] = 0;
			tDir.v[2] = 0;
			// dir->v[0] = 1;
			// dir->v[1] = 0;
			// dir->v[2] = 0;
	}

	t3d_vec3_lerp(dir, dir, &tDir, delta*3.25);

	// dir->v[0] = lerp_angle(dir->v[0], vt0, delta);
	// dir->v[1] = lerp_angle(dir->v[1], vt1, delta);
	// dir->v[2] = lerp_angle(dir->v[2], vt2, delta);


	//conso
	//printf("ANGLE : %.4f", angle);
	//rdpq_text_printn(NULL, FONT_BUILTIN_DEBUG_MONO, 220*2, 20*2, "Angle  : %.4f", angle);
	//return dir;
}

void on_switch_end(int ovfl) {
	can_switch_gs = true;

	
	// console_clear();

	// printf("timer ended");

	// console_render();
}

// void timer_func() {
	
// }

void state_switch(int16_t new_state, timer_link_t *sd, xm64player_t *xm) {
	//if can switch:
	if(can_switch_gs == false) return;

	if(mixer_ch_playing(0)) xm64player_close(xm);
	

	//? play OUR sfx here!

	// if(new_state > 3) {
	// 	gstate = 0;
	// 	return;
	// } 
	
	// if (new_state < 0) {
	// 	gstate = 3;
	// 	return;
	// }

	

	// switch(new_state) {
	// 	//case FISH:
	// 	case AQUA:
			
	// 	case SHOP:
			
	// 	//case SHELF:
	// 	default:
	// 		xm64player_stop(xm);
	// }

	

	if (new_state < 0) {
		gstate = SHELF;
	} else if(new_state > 3) {
		gstate = FISH;
	} else {
		gstate = new_state;
	}

	state_init(xm);
	
	can_switch_gs = false;
	sd = new_timer(TIMER_TICKS(450000), TF_ONE_SHOT, on_switch_end);
	
	//can switch false, start timer makes true
}


float get_time_s() { return (float)((double)get_ticks_ms() / 1000.0); }
float get_time_ms() { return (float)((double)get_ticks_us() / 1000.0); }

[[noreturn]]
int main() {

		debug_init_isviewer();
		debug_init_usblog();
		asset_init_compression(2);

	//! ======== AUDIO SETUP ========
	audio_init(48000, 4);
	mixer_init(10);

	xm64player_t xm;


	


	dfs_init(DFS_DEFAULT_LOCATION);

	display_init(RESOLUTION_640x480, DEPTH_16_BPP, FB_COUNT, GAMMA_NONE, FILTERS_RESAMPLE_ANTIALIAS);

	display_set_fps_limit(30.f);

	rdpq_init();
	joypad_init();

	//joypad_inputs_t padInputs;

	t3d_init((T3DInitParams){});

	T3DViewport viewport = t3d_viewport_create_buffered(FB_COUNT);
	rdpq_text_register_font(FONT_BUILTIN_DEBUG_MONO, rdpq_font_load_builtin(FONT_BUILTIN_DEBUG_MONO));

	rspq_block_t *dpls[MODEL_TYPE];
	T3DModel *models[MODEL_TYPE] = {
		//load models here
		t3d_model_load("rom:/rump2.t3dm"),	// INDEX 0 is gonna be the room, dont make actor from it? unknown
		t3d_model_load("rom:/fish_quad.t3dm") // INDEX 1 is fish
		//t3d_model_load("rom:/cube0.t3dm"),
		
		
		
	};

	sprite_t *button_textures[SHOP_BTN_NO] = {
		sprite_load("rom:/dark.ci8.sprite"), // 0: debug black(ish) square
		sprite_load("rom:/hand.ci8.sprite") // 1: again, test
	};

	// const char *button_textures[1] = {
	// 	"rom:/dark.ci8.sprite" // 0: debug black(ish) square
	// };
	
	//int models_size = sizeof(models)/sizeof(T3DModel);

	//const int triCount[2] = {14,2}; // ah. hardcoded lol

	// T3DMaterial *mat = t3d_model_get_material(models[1], "buppin.ci8.png");

	// T3DObject *obj = t3d_model_get_object(models[1]);

	for(int i=0; i<MODEL_TYPE; ++i) {
		
		//t3d_model_draw_material(&mat,NULL);
		//t3d_model_draw_object(obj, NULL);

		rspq_block_begin();
		t3d_model_draw(models[i]);
		dpls[i] = rspq_block_end();
	}

	//? Fish Block?


	Actor actors[ACTOR_COUNT];


	for(int j=0; j<ACTOR_COUNT; ++j) {
		actors[j] = actor_create(j, dpls[j*3 % MODEL_TYPE]);
	}

	// GUI arrays probably
	tex_button_t shopButtons[SHOP_BTN_NO];

	for(uint8_t i = 0; i<SHOP_BTN_NO; ++i) {

		float target_x = 320/2.0f;
		float tmpscalar = i * (640/4.0f);
		float target_y = 250.f;
		target_x += tmpscalar;

		shopButtons[i] = new_tex_button(button_textures[0], target_x, target_y, 2.0f, 32.f, 32.f, "BOOO", 0.f, 0.f);
	}


	int fishCount = 12;
	fish_t fish_storage[fishCount];
	
	uint8_t id = 0;
	for (int fc = 0; fc<fishCount; ++fc ) { 
		fish_storage[fc] = fish_create(id, dpls[1*3 % MODEL_TYPE], fc);
	}
	// i cant tell if i intend to have fish just be actors? or a new fish type with more, eg starve timer

	const T3DVec3 camPos = {{0.0f, 10.0f, 0.f}};
	T3DVec3 camTarget = {{0,0,0}};
	T3DVec3 camDir = {{-1,0,0}};
	

	uint8_t colorAmbient[4] = {80,50,50, 0xFF};
	T3DVec3 lightDirVec = {{1.0f, 1.0f, 0.0f}};
	uint8_t lightDirColor[4] = {120,120,120, 0xFF};
	t3d_vec3_norm(&lightDirVec);

	int actorCount = 2;

	//int fishCount = 1;


	//? @timers
	timer_init();

	timer_link_t *switch_delay;
	//timer_link_t *just_pressed_time;
	

	state_init(&xm);

	// init actors?



	// ====== 2d sprite based actors ======
	create_sprite_actor(0, display_get_width()/2, display_get_height()/2); //todo this is the hand pointer, should be idx 0.

	
	//create_sprite_actor(1, 0.f, 0.f);

	bool isa_justpress = false;
	bool can_apress = true;

	can_switch_gs = true;
	for(;;) {
		//! ======== UPDATE LOOP ========

		

		joypad_poll();
		joypad_inputs_t joypad = joypad_get_inputs(JOYPAD_PORT_1);

		//joypad_8way_t analog = joypad_get_direction(JOYPAD_PORT_1, JOYPAD_2D_STICK);

		//joypad.stick_x;

		int16_t gs = (int16_t)gstate;

		//! ======== INPUT IG ========
		if(joypad.btn.l) {
			state_switch(gs-1, switch_delay, &xm);
		} 
		
		if(joypad.btn.r) {
			state_switch(gs+1, switch_delay, &xm);
		}

		
		bool inbounds = false;
		bool *bounds_ptr = &inbounds;

		if(can_apress && joypad.btn.a) {
			//isa_justpress = true;
			for(uint8_t i = 0; i<SHOP_BTN_NO; ++i) {
				btn_input(&shopButtons[i], spriteActors[0], bounds_ptr);
				
			}
			can_apress = false;
		} else if(!joypad.btn.a) {
			can_apress = true;
		}

		// if(isa_justpress) {
			
		// 	isa_justpress = false;
		// }

		

		frameIdx = (frameIdx + 1) % FB_COUNT;

		if(actorCount < 0)actorCount = 0;
		if(actorCount > ACTOR_COUNT)actorCount = ACTOR_COUNT;

		if(fishCount < 0) fishCount = 0;
		if(fishCount > MAX_FISH) fishCount = MAX_FISH;

		float newTime = get_time_s();
		float deltaTime = (newTime - objTimeLast) * baseSpeed;
		objTimeLast = newTime;
		objTime += deltaTime;

		float timeUpdate = get_time_ms();

		if(audio_can_write()) {
			short *buf = audio_write_begin();

			mixer_poll(buf, audio_get_buffer_length());

			//mixer_try_play();

			audio_write_end();
		}

		for(int i=0; i<ACTOR_COUNT; ++i) {
			actor_update(&actors[i]);
		}

		for(int f=0; f<fishCount; ++f) {
			fish_update(&fish_storage[f], deltaTime);
		}

		update_sprite_actors(joypad);
		// Gamestate check?
		
		state_update(deltaTime, &camDir);

		camTarget.v[0] = camPos.v[0] + camDir.v[0];
		camTarget.v[1] = camPos.v[1] + camDir.v[1];
		camTarget.v[2] = camPos.v[2] + camDir.v[2];

		timeUpdate = get_time_ms() - timeUpdate;

		t3d_viewport_set_projection(&viewport, T3D_DEG_TO_RAD(55.0f), 1.0f, 1000.0f);
		//t3d_viewport_set_ortho(&viewport, -320, 320, 240, -240, 1.0f, 100.0f);
		t3d_viewport_look_at(&viewport, &camPos, &camTarget, &(T3DVec3){{0,1,0}});

		
		//! ======== DRAW 3D ========

		rdpq_attach(display_get(), display_get_zbuf());

		t3d_frame_start();
		t3d_viewport_attach(&viewport);
		//rdpq_mode_zbuf();

		rdpq_set_prim_color(RGBA32(0, 0, 0, 0xFF));

		t3d_screen_clear_color(RGBA32(100,120,220,0xFF));
		t3d_screen_clear_depth();

		t3d_light_set_ambient(colorAmbient);
		t3d_light_set_directional(0, lightDirColor, &lightDirVec);
		t3d_light_set_count(1);

		//t3d_vert

		t3d_matrix_push_pos(1);
		//rspq_block_run(dpls[0]); // Draw Room?
		for(int i=0; i<actorCount; ++i) {
			if (i==1) {
				continue;
			}
			actor_draw(&actors[i]);
		}

		if( gstate == AQUA) {
			for(int f=0;f<fishCount; ++f) {
				fish_draw(&fish_storage[f]);
			}
		} //else if (gstate == SHOP)
		//{
			/* code */
		//}
		
		

		t3d_matrix_pop(1);

		
		rdpq_sync_pipe();

		// int totalTris = 0;
		// for(int i=0; i<actorCount; ++i) {
		// 	totalTris += triCount[(i*3) % 2];
		// }

		// um draw pointer

		//rdp_detach_display();

		rdpq_set_mode_standard();
		rdpq_mode_filter(FILTER_POINT);
		rdpq_mode_alphacompare(1);
		rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);

		//! ======== DRAW 2D PRE-UI ========
		
		//rdpq_clear(RGBA32(0, 0, 0, 0xFF));

		//! ======== INTERACTIVE UI LAYER ========
		//rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
		if(gstate == SHOP) {
			for(uint8_t i = 0; i<SHOP_BTN_NO; ++i) {
				draw_tex_button(&shopButtons[i]);
				
			}
		}

		

		//! ======== DRAW 2D POST-UI ========

		draw_sprite_actors();

		//graphics_set_trans_pride() 
		

		//rdpq_set_mode_copy(false);
		//rdpq_mode_combiner(RDPQ_COMBINER_TEX);
		//rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
		//rspq_wait();
		

		// TEXT STUFF DEBUG
		//rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, 16*2, 210*2, "	   [C] Actors: %d", actorCount);
		//rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, 16, 220, "[STICK] Speed : %.2f", baseSpeed);



		//rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, 200*2, 200*2, "Triangles: %d", totalTris);
		rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, 200*2, 210*2, "Update   : %.2fms", timeUpdate);
		rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, 200*2, 220*2, "FPS      : %.2f", display_get_fps());

		rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, 200*2, 16*2, "State    : %s", state_strs[gstate]);

		//rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, 200*2, 32*2, "fish pos : %.2f, %.2f, %.2f", actors[1].pos[0], actors[1].pos[1], actors[1].pos[2]); kinda pointless now
		rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, 200*2, 32*2, "a press: %d inbounds?: %d", isa_justpress, inbounds);

		//rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, 16*2, 16*2, "Stick    : %+04d,%+04d", joypad.stick_x, joypad.stick_y);

		//rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, 16*2, 60*2, "Angle  : %.2f", angle);

		//rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, 16, 40, "room : %.2f, %.2f, %.2f", actors[0].pos[0], actors[0].pos[1], actors[0].pos[2]);

		rdpq_detach_show();
	}

	delete_timer(switch_delay);
	timer_close();

	
	t3d_destroy();
	//while(1) ;
}