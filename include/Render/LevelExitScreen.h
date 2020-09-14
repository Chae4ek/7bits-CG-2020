#pragma once

#include "ECS/Components/GameStats.h"
#include "IScreen.h"
#include "Tools/Localization.h"

class LevelExitScreen : protected IScreen {
 private:
  const GameStats* player_stats;
  const Localization* localization;

 public:
  LevelExitScreen(const GameStats* player_stats, const Localization* localization);

  void Update() const;
};