#pragma once

#include "ECS/Components/GameStats.h"
#include "IScreen.h"

class LevelExitScreen : protected IScreen {
 private:
  const GameStats* player_stats;

 public:
  explicit LevelExitScreen(const GameStats* player_stats);

  void Update() const;
};