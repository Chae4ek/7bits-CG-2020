#include "ECS/Systems.h"

Screen::Screen(Entity &player) :
	player_pos(player.Get<Position>()),
	player_sprite(player.Get<Sprite>()) {}

void Screen::Update()
{
	// TODO: delete and optimize this later
	terminal_clear();
	
	// TODO: custom output
	terminal_color(player_sprite->color);
	terminal_put(player_pos->pos_x, player_pos->pos_y, player_sprite->texture);
	
	terminal_refresh();
}