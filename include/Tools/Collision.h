#pragma once

#include "ECS/Components/ChestType.h"
#include "ECS/Components/Defense.h"
#include "ECS/Components/GameStats.h"
#include "ECS/Components/Inventory.h"
#include "ECS/Components/LevelExit.h"
#include "ECS/Components/Type.h"
#include "ECS/Components/Weapon.h"
#include "Tools/MapManager.h"

class Collision {
 private:
  MapManager *map_manager;
  Entity *player;

 public:
  Collision(MapManager *map_manager, Entity *player);

  ENTITY_TYPE GetType(const entity_ptr entity) const;
  void CollidePlayer(entity_ptr entity);

  void AttackingEnemy(const Entity *mob);
  // 0 - drop item, 1 - attacked, 2 - attacked and broke
  int TryToAttack(Weapon *weapon);

  void PickUpItem(entity_ptr entity);
};