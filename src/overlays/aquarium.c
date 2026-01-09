#include "actor2d.h"
#include "fish.h"

typedef struct aquarium_actor_s {
	actor2d_t actor;


} aquarium_actor_t;



static void init(actor2d_t *actor) {

}

static bool update(actor2d_t *actor, joypad_inputs_t pad) {
	aquarium_actor_t *this = (aquarium_actor_t *)actor;


	return true;
}

actor2d_class_t aqua_actor_class = {sizeof(aquarium_actor_t), init, update};