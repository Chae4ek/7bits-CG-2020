#pragma once

#include "ECS/Systems.h"
#include "Render/Screen.h"

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

  void InputLevelExit(const int key);
  void UpdateLevelExit();
};