#include "actor2d.h"

typedef struct pointer_actor_s {
	actor2d_t actor;
	float spawn_x;
	float spawn_y;
	float radius;
} pointer_actor_t;

static void init(actor2d_t *actor) {
	pointer_actor_t *this = (pointer_actor_t *)actor;
	this->spawn_x = actor->x;
	this->spawn_y = actor->y;

	//setup for slurping coins and stuff?
	this->radius = 16.0f;
}

static bool update(actor2d_t *actor, joypad_inputs_t pad) {
	pointer_actor_t *this = (pointer_actor_t *)actor;

	const float speed = 0.1f; // more like sensitivity but im lazy now

	

	this->actor.x += pad.stick_x * speed;
	this->actor.y -= pad.stick_y * speed;

	//? clamp positions
	if (this->actor.x + 32.f > 640.f) {
		this->actor.x = 640.f - 32.f;
	} else if (this->actor.x < 0.f) {
		this->actor.x = 0.f;
	}
	

	if (this->actor.y + 32.f > 480.f) {
		this->actor.y = 480.f - 32.f;
	} else if (this->actor.y < 0.f) {
		this->actor.y = 0.f;
	}

	// if(pad.stick_x!=0 || pad.stick_y!=0) {
	// 	rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, 16, 16, "Stick    : %+04d,%+04d", pad.stick_x, pad.stick_y);
	// }
	//rdpq_text_printf(NULL, FONT_BUILTIN_DEBUG_MONO, 50, 16, "wow yay");

	return true;
}

actor2d_class_t sprite_actor_class = {sizeof(pointer_actor_t), init, update };