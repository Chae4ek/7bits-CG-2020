#pragma once

#include "ECS/IComponent.h"

class Controls : public IComponent {
 public:
  const int KEY_LEFT;
  const int KEY_RIGHT;
  const int KEY_UP;
  const int KEY_DOWN;

  const int KEY_ENTER;
  const int KEY_ESC;

  const int KEY_1;
  const int KEY_2;
  const int KEY_3;
  const int KEY_4;
  const int KEY_5;
  const int KEY_6;
  const int KEY_7;
  const int KEY_8;

  Controls(const int KEY_LEFT, const int KEY_RIGHT, const int KEY_UP, const int KEY_DOWN, const int KEY_ENTER,
           const int KEY_ESC, const int KEY_1, const int KEY_2, const int KEY_3, const int KEY_4, const int KEY_5,
           const int KEY_6, const int KEY_7, const int KEY_8)
      : KEY_LEFT(KEY_LEFT),
        KEY_RIGHT(KEY_RIGHT),
        KEY_UP(KEY_UP),
        KEY_DOWN(KEY_DOWN),
        KEY_ENTER(KEY_ENTER),
        KEY_ESC(KEY_ESC),
        KEY_1(KEY_1),
        KEY_2(KEY_2),
        KEY_3(KEY_3),
        KEY_4(KEY_4),
        KEY_5(KEY_5),
        KEY_6(KEY_6),
        KEY_7(KEY_7),
        KEY_8(KEY_8) {}
};