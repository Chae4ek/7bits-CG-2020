#pragma once

#include "ECS/IComponent.h"

class Controls : public IComponent {
 public:
  const int KEY_LEFT;
  const int KEY_RIGHT;
  const int KEY_UP;
  const int KEY_DOWN;

  const int KEY_ENTER;

  Controls(const int KEY_LEFT, const int KEY_RIGHT, const int KEY_UP, const int KEY_DOWN, const int KEY_ENTER)
      : KEY_LEFT(KEY_LEFT), KEY_RIGHT(KEY_RIGHT), KEY_UP(KEY_UP), KEY_DOWN(KEY_DOWN), KEY_ENTER(KEY_ENTER) {}
};