#include "ECS/Systems.h"

Screen::Screen(MapManager &map_manager, Entity &player, Sprite &wall_sprite) :
	map_manager(&map_manager),
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
	int x = player_pos->pos_x % map_manager->size_x;
	int y = player_pos->pos_y % map_manager->size_y;
	if (x < 0) x += map_manager->size_x;
	if (y < 0) y += map_manager->size_y;
	terminal_put(x, y, player_sprite->texture);
	
	auto entity = map_manager->entities[map_manager->GetChunkCoords()].begin();
	auto end = map_manager->entities[map_manager->GetChunkCoords()].end();
	while (entity != end)
	{
		terminal_color((*entity)->Get<Sprite>()->color);
		terminal_put((*entity)->Get<Position>()->pos_x, (*entity)->Get<Position>()->pos_y, (*entity)->Get<Sprite>()->texture);
		
		++entity;
	}
}
void Screen::PostUpdate()
{
	terminal_color(wall_sprite->color);
	for (int i = 0; i < map_manager->size_x; ++i)
		terminal_put(i, map_manager->size_y, wall_sprite->texture);
	
	terminal_color(COLOR_WHITE);
	terminal_print(1, map_manager->size_y + 2, "Coins = ");
	terminal_color(COLOR_YELLOW);
	terminal_printf(9, map_manager->size_y + 2, "%d", player_stats->coins);
	terminal_color(COLOR_WHITE);
	terminal_print(1, map_manager->size_y + 4, "Step count = ");
	terminal_color(COLOR_YELLOW);
	terminal_printf(14, map_manager->size_y + 4, "%d", player_stats->step_count);
	
	terminal_refresh();
}