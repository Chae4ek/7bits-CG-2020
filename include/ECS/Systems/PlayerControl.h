#pragma once

#include "ECS/Components/Controls.h"
#include "Tools/Commands.h"

class PlayerControl {
 private:
  Entity *player;
  MapManager *map_manager;

  Position *position;
  const Controls *controls;
  GameStats *game_stats;

 public:
  PlayerControl(Entity *player, MapManager *map_manager);

  void Update(const int key);
};