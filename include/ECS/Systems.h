#pragma once

#include "Tools/Commands.h"

class PlayerControl {
 private:
  Entity *player;
  MapManager *map_manager;

  Position *position;
  Controls *controls;
  GameStats *game_stats;

 public:
  explicit PlayerControl(Entity *player, MapManager *map_manager);

  void Update(int key);

  constexpr int GetPosX();
  constexpr int GetPosY();
};