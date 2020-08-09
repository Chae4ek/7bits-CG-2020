#pragma once

#include "ECS/Components/GameStats.h"
#include "IScreen.h"

class GUIScreen : protected IScreen {
 private:
  const MapManager *map_manager;

  const GameStats *player_stats;

 public:
  GUIScreen(const MapManager *map_manager, const GameStats *player_stats);

  void Update() const;
};