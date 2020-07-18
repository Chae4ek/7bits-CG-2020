#pragma once

#include "Advanced.h"
#include "ECS/Systems.h"

class Game {
 private:
  Entity player;

  Sprite wall_sprite;

  MapManager map_manager;

  PlayerControl player_control;
  GenerateMap generate_map;
  Collision collision;
  Screen screen;

 public:
  Game();

  void Run();

  void Clear();
  int Input();
  void Update();
  void Render();
};