#pragma once

#include "ECS/IComponent.h"

class MenuProperties : public IComponent {
 public:
  bool exit = false;
  int cursor = 0;

  bool in_menu;
  bool new_graphics;

  MenuProperties(const bool in_menu, const bool new_graphics) : in_menu(in_menu), new_graphics(new_graphics) {}
};