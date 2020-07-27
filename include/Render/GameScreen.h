#pragma once

#include "IScreen.h"

class GameScreen : protected IScreen {
 private:
  const MapManager *map_manager;

  const Position *player_pos;
  const Sprite *player_sprite;

 public:
  GameScreen(const MapManager *map_manager, const Entity *player);

  void Update() const;
};