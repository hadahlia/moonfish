#ifndef __GLOBAL_H
#define __GLOBAL_H

//static int playerMoney;
// static int fishCount;
#include <stdint.h>

typedef struct playerstats_s {
	int money;
	int fishCount;
} playerstats_t;

playerstats_t create_stats(int money, int fishCount);

#endif