#pragma once

#include <string>
#include <vector>

#include "ECS/IComponent.h"

class MenuProperties : public IComponent {
 public:
  bool exit = false;
  int cursor = 0;

  bool in_menu;
  bool new_graphics;

  int local_id = 0;
  const std::vector<std::string> locals;

  MenuProperties(const bool in_menu, const bool new_graphics, const std::vector<std::string> locals)
      : in_menu(in_menu), new_graphics(new_graphics), locals(locals) {}
};