#pragma once

#include "ECS/Components/Defense.h"
#include "ECS/Components/GameStats.h"
#include "ECS/Components/Inventory.h"
#include "ECS/Components/Type.h"
#include "ECS/Components/Weapon.h"
#include "IScreen.h"

class GUIScreen : protected IScreen {
 private:
  const MapManager *map_manager;

  const GameStats *player_stats;
  const Inventory *player_inv;
  const Defense *player_def;

  const int pos_inv_x;
  const int pos_inv_y;
  const int pos_stats_x;
  const int pos_stats_y;

 public:
  GUIScreen(const MapManager *map_manager, const Entity *player);

  void Update() const;
};