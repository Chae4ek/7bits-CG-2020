#include "Render/LevelExitScreen.h"

LevelExitScreen::LevelExitScreen(const GameStats* player_stats, const Localization* localization)
    : player_stats(player_stats), localization(localization) {}

void LevelExitScreen::Update() const {
  terminal_clear();

  Print(COLOR_AQUA, 1, 1, "%s", localization->local.at("press_for_continue").c_str());

  Print(COLOR_WHITE, 1, 4, "%s = ", localization->local.at("coins").c_str());
  Print(COLOR_YELLOW, 20, 4, "%d", player_stats->coins);
  Print(COLOR_WHITE, 1, 6, "%s = ", localization->local.at("step_count").c_str());
  Print(COLOR_YELLOW, 20, 6, "%d", player_stats->step_count);

  terminal_refresh();
}