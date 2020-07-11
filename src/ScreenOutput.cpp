#include <BearLibTerminal.h>
#include "ScreenOutput.h"
#include "GenerateMap.h"

Screen::Screen(Player &player) : player(&player) {}

Map map(1);
double smooth = 12.5;

void Screen::Output()
{
	for (int i = 0; i < TK_WIDTH; ++i)
	{
		for (int j = 0; j < TK_HEIGHT; ++j)
		{
			if (map.PerlinNoise(i / smooth, j / smooth) > 0.2) terminal_put(i, j, '#');
		}
	}
	
	terminal_put(player->GetPosX(), player->GetPosY(), PLAYER);
}