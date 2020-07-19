#pragma once

#include "Advanced.h"
#include "ECS/Systems.h"

class Game {
 private:
  Entity player;

  MapManager map_manager;

  PlayerControl player_control;
  Screen screen;

 public:
  explicit Game(const unsigned int seed);

  void Run();

  int Input();
  void Update();
  void Render();
};