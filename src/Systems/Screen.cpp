#include "ECS/Systems.h"

Screen::Screen(Position *player) : player(player) {}

void Screen::Update()
{
	// TODO: delete and optimize this later
	terminal_clear();
	
	terminal_put(player->pos_x, player->pos_y, SPRITE_PLAYER);
	
	terminal_refresh();
}