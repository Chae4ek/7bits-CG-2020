#include <BearLibTerminal.h>
#include "ScreenOutput.h"
#include "GenerateMap.h"

Screen::Screen(Player &player) : player(&player) {}

Map map(1);
double smooth = 60;
double threshold = 0.125;
double sharp = 0.009;
int x_add = 0;
int y_add = 0;

void Screen::Output()
{
	terminal_color("grey");
	for (int i = 0; i < TK_WIDTH; ++i)
	{
		for (int j = 0; j < TK_HEIGHT; ++j)
		{
			if (map.isWall(i + x_add, j + y_add)) terminal_put(i, j, '#');
		}
	}
	
	terminal_color("yellow");
	terminal_put(player->GetPosX(), player->GetPosY(), PLAYER);
	
	// For debug
	// TODO: delete this later
	terminal_color("red");
	terminal_printf(0, 0, "<12> smooth = %lf", map.smooth);
	terminal_printf(0, 1, "<34> threshold = %lf", map.threshold);
	terminal_printf(0, 2, "<56> sharp = %lf", map.sharp);
	
	int key = terminal_peek();
	if (key == TK_1) map.smooth += 0.1;
	if (key == TK_2) map.smooth -= 0.1;
	if (key == TK_3) map.threshold += 0.01;
	if (key == TK_4) map.threshold -= 0.01;
	if (key == TK_5) map.sharp += 0.001;
	if (key == TK_6) map.sharp -= 0.001;
	if (key == TK_LEFT) --x_add;
	if (key == TK_RIGHT) ++x_add;
	if (key == TK_UP) --y_add;
	if (key == TK_DOWN) ++y_add;
}