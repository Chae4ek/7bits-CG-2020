#pragma once

#include "ECS/Components/Controls.h"
#include "Tools/Commands.h"

class LevelExitControl {
 private:
  MapManager *map_manager;

  Position *player_pos;
  const Controls *controls;

 public:
  LevelExitControl(Entity *player, MapManager *map_manager);

  void Update(const int key);
};