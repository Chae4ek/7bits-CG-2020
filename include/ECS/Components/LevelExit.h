#pragma once

#include "ECS/IComponent.h"

class LevelExit : public IComponent {
 public:
  const int level;

  explicit LevelExit(const int level) : level(level) {}
};