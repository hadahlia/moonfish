#ifndef __SOUND_PLAYER_H
#define  __SOUND_PLAYER_H

#include <libdragon.h>

//wav64_t wav;

void play_sound(wav64_t *wav, const char *fn, int ch);

#endif