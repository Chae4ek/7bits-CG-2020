#include <BearLibTerminal.h>
#include "ScreenOutput.h"
#include "GenerateMap.h"

Screen::Screen(Player &player) : player(&player) {}

Map map(1);
double smooth = 60;
double threshold = 0.125;
double sharp_offset = 0.9;
double sharp = 0.007;
int x_add = 0;
int y_add = 0;

void Screen::Output()
{
	terminal_color("grey");
	for (int i = 0; i < TK_WIDTH; ++i)
	{
		for (int j = 0; j < TK_HEIGHT; ++j)
		{
			double noise = map.PerlinNoise((i + x_add) / smooth, (j + y_add) / smooth);
			if (noise > threshold || noise / sharp_offset > threshold && noise / sharp_offset < threshold + sharp)
				terminal_put(i, j, '#');
		}
	}
	
	terminal_color("yellow");
	terminal_put(player->GetPosX(), player->GetPosY(), PLAYER);
	
	terminal_color("red");
	terminal_printf(0, 0, "<12> smooth = %lf", smooth);
	terminal_printf(0, 1, "<34> threshold = %lf", threshold);
	terminal_printf(0, 2, "<56> sharp_offset = %lf", sharp_offset);
	terminal_printf(0, 3, "<78> sharp = %lf", sharp);
	terminal_color("white");
	
	int key = terminal_peek();
	if (key == TK_1) smooth += 0.1;
	if (key == TK_2) smooth -= 0.1;
	if (key == TK_3) threshold += 0.01;
	if (key == TK_4) threshold -= 0.01;
	if (key == TK_5) sharp_offset += 0.01;
	if (key == TK_6) sharp_offset -= 0.01;
	if (key == TK_7) sharp += 0.001;
	if (key == TK_8) sharp -= 0.001;
	if (key == TK_LEFT) --x_add;
	if (key == TK_RIGHT) ++x_add;
	if (key == TK_UP) --y_add;
	if (key == TK_DOWN) ++y_add;
}