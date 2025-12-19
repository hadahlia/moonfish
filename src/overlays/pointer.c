#include "actor2d.h"

typedef struct pointer_actor_s {
	actor2d_t actor;
	float spawn_x;
	float spawn_y;
} pointer_actor_t;

static void init(actor2d_t *actor) {
	pointer_actor_t *this = (pointer_actor_t *)actor;
	this->spawn_x = actor->x;
	this->spawn_y = actor->y;
}

static bool update(actor2d_t *actor, joypad_inputs_t pad) {
	pointer_actor_t *this = (pointer_actor_t *)actor;

	// if(pad.stick_x!=0 || pad.stick_y!=0) {
	// 	rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, 16, 16, "Stick    : %+04d,%+04d", pad.stick_x, pad.stick_y);
	// }
	rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, 50, 16, "wow yay");

	return true;
}

actor2d_class_t sprite_actor_class = {sizeof(pointer_actor_t), init, update };