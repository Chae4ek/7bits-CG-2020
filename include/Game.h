#pragma once

#include "ECS/Components/Defense.h"
#include "ECS/Systems/LevelExitControl.h"
#include "ECS/Systems/MenuControl.h"
#include "ECS/Systems/PlayerControl.h"
#include "Render/GUIScreen.h"
#include "Render/GameScreen.h"
#include "Render/LevelExitScreen.h"
#include "Render/MenuScreen.h"

class Game {
 private:
  MenuProperties menu_prop;

  Entity player;

  MapManager map_manager;

  PlayerControl player_control;
  LevelExitControl level_exit_control;
  MenuControl menu_control;

  GameScreen game_screen;
  GUIScreen gui_screen;
  LevelExitScreen level_exit_screen;
  MenuScreen menu_screen;

 public:
  explicit Game(const unsigned int start_seed);

  void Run();

  int Input();
  void Update();
  void Render() const;

  void RenderLevelExit() const;

  void RenderMenu() const;
};