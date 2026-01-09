#include "actor2d.h"

typedef struct menu_actor_s {
	actor2d_t actor;
} menu_actor_t;

static void init(actor2d_t *actor) {
	//menu_actor_t *this = (menu_actor_t *)actor;
}


static bool update(actor2d_t *actor, joypad_inputs_t pad) {
	//menu_actor_t *this = (menu_actor_t *)actor;

	return true;
}


actor2d_class_t sprite_actor_class = {sizeof(menu_actor_t), init, update };