#include "Render/Screen.h"

Screen::Screen(const MapManager *map_manager, const Entity *player)
    : map_manager(map_manager),
      player_pos(player->Get<Position>()),
      player_sprite(player->Get<Sprite>()),
      player_stats(player->Get<GameStats>()) {}

void Screen::Update() {
  // TODO: delete and optimize this later
  terminal_clear();

  Position player_local_pos = map_manager->GlobalToLocal(player_pos);
  Print(player_local_pos.pos_x, player_local_pos.pos_y, player_sprite);

  chunk_coords_t current_chunk = map_manager->GetChunkCoords(player_pos);
  if (map_manager->ChunkIsEmpty(current_chunk)) return;

  entity_t entity = map_manager->entities.at(current_chunk).begin();
  entity_t end = map_manager->entities.at(current_chunk).end();
  while (entity != end) {
    Print((*entity)->Get<Position>()->pos_x, (*entity)->Get<Position>()->pos_y, (*entity)->Get<Sprite>());
    ++entity;
  }
}
void Screen::UpdateGUI() {
  terminal_color(_COLOR_BLUE);
  for (int i = 0; i < map_manager->size_x; ++i) terminal_put(i, map_manager->size_y, TEXTURE_WALL);

  Print(_COLOR_WHITE, 1, map_manager->size_y + 2, "Coins = ");
  Print(_COLOR_YELLOW, 9, map_manager->size_y + 2, "%d", player_stats->coins);
  Print(_COLOR_WHITE, 1, map_manager->size_y + 4, "Step count = ");
  Print(_COLOR_YELLOW, 14, map_manager->size_y + 4, "%d", player_stats->step_count);

  terminal_refresh();
}

void Screen::UpdateLevelExit() {
  terminal_clear();

  Print(_COLOR_AQUA, 1, 1, "Press [[ENTER]] for continue");

  Print(_COLOR_WHITE, 1, 4, "Coins = ");
  Print(_COLOR_YELLOW, 9, 4, "%d", player_stats->coins);
  Print(_COLOR_WHITE, 1, 6, "Step count = ");
  Print(_COLOR_YELLOW, 14, 6, "%d", player_stats->step_count);

  terminal_refresh();
}

inline void Screen::Print(int x, int y, const Sprite *sprite) {
  terminal_color(sprite->color);
  terminal_put(x, y, sprite->texture);
}
template<class... Args>
inline void Screen::Print(color_t color, int x, int y, const char *s, Args... args) {
  terminal_color(color);
  terminal_printf(x, y, s, args...);
}