#pragma once

#include "ECS/IComponent.h"

class GameStats : public IComponent {
 public:
  int coins = 0;
  int step_count = 0;
};