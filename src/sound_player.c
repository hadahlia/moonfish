#include "sound_player.h"

//wav64_t wav;

void play_sound(wav64_t *wav, const char *fn, int ch) {
	wav64_open(wav, fn);

	wav64_play(wav, ch);
}