#pragma once

#include "ECS/Components/Defense.h"
#include "ECS/Components/GameStats.h"
#include "ECS/Components/Inventory.h"
#include "ECS/Components/MenuProperties.h"
#include "ECS/Components/Sprite.h"
#include "ECS/Components/Type.h"
#include "ECS/Components/Weapon.h"
#include "IScreen.h"
#include "Tools/Collision.h"

class GUIScreen : protected IScreen {
 private:
  const MapManager *map_manager;
  const Entity *player;
  const MenuProperties *menu_prop;

  const GameStats *player_stats;
  const Inventory *player_inv;
  const Defense *player_def;
  const Position *player_pos;

  const int pos_inv_x;
  const int pos_inv_y;
  const int pos_stats_x;
  const int pos_stats_y;

 public:
  GUIScreen(const MapManager *map_manager, const Entity *player, const MenuProperties *menu_prop);

  void Update() const;
};