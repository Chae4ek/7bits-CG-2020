#pragma once

#include "ECS/IComponent.h"

class Controls : public IComponent {
 public:
  int KEY_LEFT;
  int KEY_RIGHT;
  int KEY_UP;
  int KEY_DOWN;

  Controls(int KEY_LEFT, int KEY_RIGHT, int KEY_UP, int KEY_DOWN)
      : KEY_LEFT(KEY_LEFT), KEY_RIGHT(KEY_RIGHT), KEY_UP(KEY_UP), KEY_DOWN(KEY_DOWN) {}
};