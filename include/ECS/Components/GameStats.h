#pragma once

#include <vector>

#include "ECS/IComponent.h"

class GameStats : public IComponent {
 public:
  int coins = 0;
  int step_count = 0;

  const int max_records = 9;
  std::vector<int> records;
};