#include "Advanced.h"
#include "ECS/Systems.h"

Screen::Screen(const MapManager &map_manager, const Entity &player, const Sprite &wall_sprite)
    : map_manager(&map_manager),
      player_pos(player.Get<Position>()),
      player_sprite(player.Get<Sprite>()),
      player_stats(player.Get<GameStats>()),
      wall_sprite(&wall_sprite) {}

void Screen::Update() {
  // TODO: delete and optimize this later
  terminal_clear();

  // TODO: merge this to custom output
  terminal_color(player_sprite->color);
  auto player_local_pos = GlobalToLocal(map_manager, player_pos->pos_x, player_pos->pos_y);
  terminal_put(player_local_pos.first, player_local_pos.second, player_sprite->texture);

  auto entity = map_manager->entities.at(map_manager->GetChunkCoords()).begin();
  auto end = map_manager->entities.at(map_manager->GetChunkCoords()).end();
  while (entity != end) {
    terminal_color((*entity)->Get<Sprite>()->color);
    terminal_put((*entity)->Get<Position>()->pos_x, (*entity)->Get<Position>()->pos_y,
                 (*entity)->Get<Sprite>()->texture);

    ++entity;
  }
}
void Screen::PostUpdate() {
  terminal_color(wall_sprite->color);
  for (int i = 0; i < map_manager->size_x; ++i) terminal_put(i, map_manager->size_y, wall_sprite->texture);

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