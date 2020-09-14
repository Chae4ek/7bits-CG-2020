#pragma once

#include "ECS/Components/MenuProperties.h"
#include "IScreen.h"

class GameScreen : protected IScreen {
 private:
  const MapManager *map_manager;

  const Position *player_pos;
  const Sprite *player_sprite;

  MenuProperties *menu_prop;

 public:
  GameScreen(const MapManager *map_manager, const Entity *player, MenuProperties *menu_prop);

  void Update() const;
};