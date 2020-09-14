#pragma once

#include "Tools/Commands.h"

class EnemyControl {
 private:
  Entity *player;
  MapManager *map_manager;

  Position *player_pos;
  GameStats *player_stats;

  int last_step_count = 0;

 public:
  EnemyControl(Entity *player, MapManager *map_manager);

  void Update();
};