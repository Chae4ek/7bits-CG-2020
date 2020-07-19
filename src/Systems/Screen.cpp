#include "Advanced.h"
#include "ECS/Systems.h"

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

  auto entity = map_manager->entities.at(map_manager->GetChunkCoords(player_pos)).begin();
  auto end = map_manager->entities.at(map_manager->GetChunkCoords(player_pos)).end();
  while (entity != end) {
    Print((*entity)->Get<Position>()->pos_x, (*entity)->Get<Position>()->pos_y, (*entity)->Get<Sprite>());
    ++entity;
  }
}

void Screen::UpdateGUI() {
  terminal_color(COLOR_GREY);
  for (int i = 0; i < map_manager->size_x; ++i) terminal_put(i, map_manager->size_y, TEXTURE_WALL);

  Print(COLOR_WHITE, 1, map_manager->size_y + 2, "Coins = ");
  Print(COLOR_YELLOW, 9, map_manager->size_y + 2, "%d", player_stats->coins);
  Print(COLOR_WHITE, 1, map_manager->size_y + 4, "Step count = ");
  Print(COLOR_YELLOW, 14, map_manager->size_y + 4, "%d", player_stats->step_count);

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