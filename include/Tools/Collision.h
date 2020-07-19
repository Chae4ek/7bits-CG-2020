#pragma once

#include "MapManager.h"

class Collision {
 private:
  MapManager *map_manager;
  Entity *player;

 public:
  Collision(MapManager *map_manager, Entity *player);

  bool ForMovePlayer(entity_ptr entity) const;
  void CollidePlayer(entity_ptr entity);
};