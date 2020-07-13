#include "ECS/Systems.h"

Screen::Screen(Entity &player) :
	player_pos(player.Get<Position>()),
	player_sprite(player.Get<Sprite>()) {}

void Screen::Update()
{
	// TODO: delete and optimize this later
	terminal_clear();
	
	terminal_put(player_pos->pos_x, player_pos->pos_y, player_sprite->sprite);
	
	terminal_refresh();
}