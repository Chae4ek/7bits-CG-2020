#pragma once

#include "Collision.h"
#include "GenerateMap.h"
#include "ICommand.h"

class MovePlayer : public ICommand {
 private:
  MapManager *map_manager;
  Entity *player;
  Position new_pos;

  Position *player_pos;
  GameStats *player_stats;

 public:
  MovePlayer(MapManager *map_manager, Entity *player, Position new_pos);
  void Execute();
};