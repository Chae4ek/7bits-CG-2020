#pragma once

#include "MapManager.h"

class PlayerControl {
 private:
  Position *position;
  Controls *controls;
  GameStats *game_stats;

 public:
  explicit PlayerControl(const Entity &player);

  void Update(int key);

  constexpr int GetPosX();
  constexpr int GetPosY();

  constexpr void Left();
  constexpr void Right();
  constexpr void Up();
  constexpr void Down();
};

class Screen {
 private:
  const MapManager *map_manager;

  const Position *player_pos;
  const Sprite *player_sprite;
  const GameStats *player_stats;

  const Sprite *wall_sprite;

 public:
  Screen(const MapManager &map_manager, const Entity &player, const Sprite &wall_sprite);

  void Update();

  void UpdateGUI();

  inline void Print(int x, int y, const Sprite *sprite);
  template<class... Args>
  inline void Print(color_t color, int x, int y, const char *s, Args... args);
};

class GenerateMap {
 private:
  const unsigned int seed;
  MapManager *map_manager;

 public:
  GenerateMap(const unsigned int seed, MapManager *map_manager);

  void Update();

  void GenerateChunk();
};

class Collision {
 private:
  MapManager *map_manager;
  const Entity *player;
  const Position *player_pos;

 public:
  Collision(MapManager *map_manager, const Entity &player);

  void Update();
};