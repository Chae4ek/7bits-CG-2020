#pragma once

#include "ECS/Components/Controls.h"
#include "Tools/Commands.h"

class PlayerControl {
 private:
  Entity *player;
  MapManager *map_manager;

  Position *player_pos;
  const Controls *controls;
  GameStats *player_stats;
  Inventory *player_inv;

 public:
  PlayerControl(Entity *player, MapManager *map_manager);

  void Update(const int key);
};