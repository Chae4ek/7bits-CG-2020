#pragma once

#include "ECS/IComponent.h"

class Position : public IComponent {
 public:
  int pos_x;
  int pos_y;

  Position(int x, int y) : pos_x(x), pos_y(y) {}
};