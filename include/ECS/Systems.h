#pragma once

#include "MapManager.h"

class PlayerControl {
 private:
  MapManager *map_manager;

  Position *position;
  Controls *controls;
  GameStats *game_stats;

 public:
  explicit PlayerControl(const Entity *player, MapManager *map_manager);

  void Update(int key);

  constexpr int GetPosX();
  constexpr int GetPosY();

  inline void Left();
  inline void Right();
  inline void Up();
  inline void Down();

  inline void TryGoToPos(const Position *new_pos);
};

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