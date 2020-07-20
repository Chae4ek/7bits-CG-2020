#pragma once

#include "Tools/MapManager.h"

class Screen {
 private:
  const MapManager *map_manager;

  const Position *player_pos;
  const Sprite *player_sprite;
  const GameStats *player_stats;

 public:
  Screen(const MapManager *map_manager, const Entity *player);

  void Update();

  void UpdateGUI();

  inline void Print(int x, int y, const Sprite *sprite);
  template<class... Args>
  inline void Print(color_t color, int x, int y, const char *s, Args... args);
};