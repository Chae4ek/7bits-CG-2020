#pragma once

#include "ECS/Components/ChestType.h"
#include "ECS/Components/GameStats.h"
#include "ECS/Components/Inventory.h"
#include "ECS/Components/LevelExit.h"
#include "ECS/Components/Type.h"
#include "Tools/MapManager.h"

class Collision {
 private:
  MapManager *map_manager;
  Entity *player;

 public:
  Collision(MapManager *map_manager, Entity *player);

  ENTITY_TYPE GetType(const entity_ptr entity) const;
  void Collide(Entity *mob, entity_ptr entity);

  void PickUpItem(entity_ptr entity);
};