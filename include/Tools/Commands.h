#pragma once

#include <memory>
#include <vector>

#include "Collision.h"
#include "ICommand.h"
#include "MapManager.h"

class MovePlayer : public ICommand {
 private:
  MapManager *map_manager;
  Entity *player;
  Position new_pos;

 public:
  MovePlayer(MapManager *map_manager, Entity *player, Position new_pos);
  void Execute() override;
};