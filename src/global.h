#ifndef __GLOBAL_H
#define __GLOBAL_H

//static int playerMoney;
// static int fishCount;
#include <stdint.h>

typedef struct playerstats_s {
	int64_t money;
	int fishCount;
} playerstats_t;

playerstats_t create_stats(int64_t money, int fishCount);

#endif