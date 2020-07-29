#include "Render/GUIScreen.h"

GUIScreen::GUIScreen(const MapManager *map_manager, const GameStats *player_stats)
    : map_manager(map_manager), player_stats(player_stats) {}

void GUIScreen::Update() const {
  terminal_color(COLOR_BLUE);
  for (int i = 0; i < map_manager->size_x; ++i) terminal_put(i, map_manager->size_y, PREFABS.at(TYPE_WALL).texture);

  Print(COLOR_WHITE, 1, map_manager->size_y + 2, "Coins = ");
  Print(COLOR_YELLOW, 9, map_manager->size_y + 2, "%d", player_stats->coins);
  Print(COLOR_WHITE, 1, map_manager->size_y + 4, "Step count = ");
  Print(COLOR_YELLOW, 14, map_manager->size_y + 4, "%d", player_stats->step_count);

  terminal_refresh();
}