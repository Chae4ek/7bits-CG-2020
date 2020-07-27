#include "Render/LevelExitScreen.h"

LevelExitScreen::LevelExitScreen(const GameStats* player_stats) : player_stats(player_stats) {}

void LevelExitScreen::Update() const {
  terminal_clear();

  Print(_COLOR_AQUA, 1, 1, "Press [[ENTER]] for continue");

  Print(_COLOR_WHITE, 1, 4, "Coins = ");
  Print(_COLOR_YELLOW, 9, 4, "%d", player_stats->coins);
  Print(_COLOR_WHITE, 1, 6, "Step count = ");
  Print(_COLOR_YELLOW, 14, 6, "%d", player_stats->step_count);

  terminal_refresh();
}