#include "ECS/Systems.h"

Screen::Screen(Entity &player, Sprite &wall_sprite) :
	player_pos(player.Get<Position>()),
	player_sprite(player.Get<Sprite>()),
	player_stats(player.Get<GameStats>()),
	wall_sprite(&wall_sprite) {}

void Screen::Update()
{
	// TODO: delete and optimize this later
	terminal_clear();
	
	// TODO: merge this to custom output
	terminal_color(player_sprite->color);
	terminal_put(player_pos->pos_x, player_pos->pos_y, player_sprite->texture);
	
	terminal_color(wall_sprite->color);
	for (int i = 0; i < terminal_state(TK_WIDTH); ++i)
		terminal_put(i, terminal_state(TK_HEIGHT) - 6, wall_sprite->texture);
	
	terminal_color(COLOR_WHITE);
	terminal_print(1, terminal_state(TK_HEIGHT) - 4, "Coins = ");
	terminal_color(COLOR_YELLOW);
	terminal_printf(9, terminal_state(TK_HEIGHT) - 4, "%d", player_stats->coins);
	terminal_color(COLOR_WHITE);
	terminal_print(1, terminal_state(TK_HEIGHT) - 2, "Step count = ");
	terminal_color(COLOR_YELLOW);
	terminal_printf(14, terminal_state(TK_HEIGHT) - 2, "%d", player_stats->step_count);
	
	terminal_refresh();
}