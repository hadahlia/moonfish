#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>

#define FB_COUNT 3

#define ACTOR_COUNT 250
#define MAX_FISH_NO 255

#define RAD_360 6.28318530718f

static float objTimeLast = 0.f;
static float objTime = 0.f;
static float baseSpeed = 1.0f;
static int frameIdx = 0;

typedef enum {FISH = 0, AQUA = 1, SHOP = 2, SHELF = 3} GameState_t;

//static enum GameState {FISH = 0, AQUA = 1, SHOP = 2, SHELF = 3} gstate = 1;
static GameState_t gstate = 1;

static char* state_strs[] = { "FISH", "AQUA", "SHOP", "SHELF"};

static volatile bool can_switch = false;



typedef struct {
	uint32_t id;
	float pos[3];
	float rot[3];
	float scale[3];

	rspq_block_t *dpl;
	T3DMat4FP *modelMat;
} Actor;

Actor actor_create(uint32_t id, rspq_block_t *dpl) {
	float randScale = (rand() % 100) / 3000.0f + 0.03f;
	Actor actor = (Actor){
		.id = id,
		.pos = {0,0,0},
		.rot = {0,0,0},
		.scale = {randScale, randScale, randScale},
		.dpl = dpl,
		.modelMat = malloc_uncached(sizeof(T3DMat4FP) * FB_COUNT)
	};
	return actor;
}

void actor_update(Actor *actor) {
	actor->pos[0] = 0;

	float randRot = (float)fm_fmodf(actor->id * 123.1f, 5.0f);
	float randDist = (float)fm_fmodf(actor->id * 4645.987f, 30.5f) + 10.0f;

	actor->rot[0] = fm_fmodf(randRot + objTime * 1.05f, RAD_360);
	actor->rot[1] = fm_fmodf(randRot + objTime * 1.03f, RAD_360);
	actor->rot[2] = fm_fmodf(randRot + objTime * 1.2f, RAD_360);

	actor->pos[0] = randDist * fm_cosf(objTime * 1.6f + randDist);
	actor->pos[1] = randDist * fm_cosf(objTime * 1.5f + randRot);
	actor->pos[2] = randDist * fm_cosf(objTime * 1.4f + randDist*randRot);


	t3d_mat4fp_from_srt_euler(&actor->modelMat[frameIdx], actor->scale, actor->rot, actor->pos);
}

void actor_draw(Actor *actor) {
	t3d_matrix_set(&actor->modelMat[frameIdx], true);
	rspq_block_run(actor->dpl);
}

void actor_delete(Actor *actor) {
	free_uncached(actor->modelMat);
}

// Shouldnt i just, init everything we will need? its all one room...
void state_init() {
	switch(gstate) {
		case 0:
			//FISH
			break;
		case 1:
			//AQUA
			break;
		case 2:
			//SHOP
			break;
		case 3:
			//SHELF
	}
}

void state_update(float delta) {
	switch(gstate) {
		case 0:
			//FISH
			break;
		case 1:
			//AQUA
			break;
		case 2:
			//SHOP
			break;
		case 3:
			//SHELF
	}
}

void state_switch(GameState_t new_state) {
	gstate = new_state;
}

void on_switch_end(int ovfl) {
	can_switch = true;

	gstate += 1;
	// console_clear();

	// printf("timer ended");

	// console_render();
}


float get_time_s() { return (float)((double)get_ticks_ms() / 1000.0); }
float get_time_ms() { return (float)((double)get_ticks_us() / 1000.0); }

[[noreturn]]
int main() {

		debug_init_isviewer();
		debug_init_usblog();
		asset_init_compression(2);

	dfs_init(DFS_DEFAULT_LOCATION);

	display_init(RESOLUTION_320x240, DEPTH_16_BPP, FB_COUNT, GAMMA_NONE, FILTERS_RESAMPLE_ANTIALIAS);

	rdpq_init();
	joypad_init();

	t3d_init((T3DInitParams){});
	T3DViewport viewport = t3d_viewport_create_buffered(FB_COUNT);
	rdpq_text_register_font(FONT_BUILTIN_DEBUG_MONO, rdpq_font_load_builtin(FONT_BUILTIN_DEBUG_MONO));

	rspq_block_t *dpls[1];
	T3DModel *models[1] = {
		//load models here
		t3d_model_load("rom:/cube0.t3dm")
	};

	const int triCount[2] = {12,60};

	//for(int i=0;i<2; ++i) {
		rspq_block_begin();
		t3d_model_draw(models[0]);
		dpls[0] = rspq_block_end();
	//}

	Actor actors[ACTOR_COUNT];


	for(int j=0; j<ACTOR_COUNT; ++j) {
		actors[j] = actor_create(j, dpls[j*3 % 2]);
	}

	Actor fish_storage[MAX_FISH_NO];
	// i cant tell if i intend to have fish just be actors? or a new fish type with more, eg starve timer

	const T3DVec3 camPos = {{100.0f, 25.0f, 0}};
	const T3DVec3 camTarget = {{0,0,0}};

	uint8_t colorAmbient[4] = {80,50,50, 0xFF};
	T3DVec3 lightDirVec = {{1.0f, 1.0f, 0.0f}};
	uint8_t lightDirColor[4] = {120,120,120, 0xFF};
	t3d_vec3_norm(&lightDirVec);

	int actorCount = 50;

	int fishCount = 1;

	timer_link_t *switch_delay;

	timer_init();

	switch_delay = new_timer(TIMER_TICKS(1000000), TF_ONE_SHOT, on_switch_end);

	//state_init();


	for(;;) {
		// ======== UPDATE LOOP ========
		joypad_poll();
		joypad_inputs_t joypad = joypad_get_inputs(JOYPAD_PORT_1);

		frameIdx = (frameIdx + 1) % FB_COUNT;

		if(actorCount < 0)actorCount = 0;
		if(actorCount > ACTOR_COUNT)actorCount = ACTOR_COUNT;

		float newTime = get_time_s();
		float deltaTime = (newTime - objTimeLast) * baseSpeed;
		objTimeLast = newTime;
		objTime += deltaTime;

		float timeUpdate = get_time_ms();
		for(int i=0; i<ACTOR_COUNT; ++i) {
			actor_update(&actors[i]);
		}
		timeUpdate = get_time_ms() - timeUpdate;

		//t3d_viewport_set_projection(&viewport, T3D_DEG_TO_RAD(65.0f), 10.0f, 100.0f);
		t3d_viewport_set_ortho(&viewport, -320/2, 320/2, 240/2, -240/2, 10.0f, 1000.0f);
		t3d_viewport_look_at(&viewport, &camPos, &camTarget, &(T3DVec3){{0,1,0}});


		// Gamestate check?

		state_update(deltaTime);


		// ======== DRAW 3D ========
		rdpq_attach(display_get(), display_get_zbuf());
		t3d_frame_start();
		t3d_viewport_attach(&viewport);

		rdpq_set_prim_color(RGBA32(0, 0, 0, 0xFF));

		t3d_screen_clear_color(RGBA32(100,120,200,0xFF));
		t3d_screen_clear_depth();

		t3d_light_set_ambient(colorAmbient);
		t3d_light_set_directional(0, lightDirColor, &lightDirVec);
		t3d_light_set_count(1);

		t3d_matrix_push_pos(1);
		for(int i=0; i<actorCount; ++i) {
			actor_draw(&actors[i]);
		}
		t3d_matrix_pop(1);

		// ======== DRAW 2D ========
		rdpq_sync_pipe();

		int totalTris = 0;
		for(int i=0; i<actorCount; ++i) {
			totalTris += triCount[(i*3) % 2];
		}

		rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, 16, 210, "	   [C] Actors: %d", actorCount);
		rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, 16, 220, "[STICK] Speed : %.2f", baseSpeed);

		rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, 200, 200, "Triangles: %d", totalTris);
		rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, 200, 210, "Update   : %.2fms", timeUpdate);
		rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, 200, 220, "FPS      : %.2f", display_get_fps());

		rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, 200, 16, "State    : %s", state_strs[gstate]);

		rdpq_detach_show();
	}

	delete_timer(switch_delay);
	timer_close();

	

	//while(1) ;
}