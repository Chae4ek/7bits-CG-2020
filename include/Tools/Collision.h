#pragma once

#include "ECS/Components/GameStats.h"
#include "ECS/Components/LevelExit.h"
#include "ECS/Components/Type.h"
#include "MapManager.h"

class Collision {
 private:
  MapManager *map_manager;
  Entity *player;

 public:
  Collision(MapManager *map_manager, Entity *player);

  bool ForMovePlayer(const entity_ptr entity) const;
  void CollidePlayer(entity_ptr entity);
};