#include "global.h"

// static int playerMoney = 0;

//static int fishCount = 0;

//struct playerstats pstats = {.money = 0, .fishCount = 0};

playerstats_t create_stats(int money, int fishCount) {

	playerstats_t pstats = (playerstats_t){
		.money = money,
		.fishCount = fishCount
	};

	return pstats;
}