#pragma once

#include "IScreen.h"

class LevelExitScreen : protected IScreen {
 private:
  const GameStats* player_stats;

 public:
  explicit LevelExitScreen(const GameStats* player_stats);

  void Update() const;
};