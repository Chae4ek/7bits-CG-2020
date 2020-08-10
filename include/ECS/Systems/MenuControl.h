#pragma once

#include "ECS/Components/Controls.h"
#include "ECS/Components/MenuProperties.h"

class MenuControl {
 private:
  MenuProperties* menu_prop;
  const Controls* controls;

 public:
  explicit MenuControl(MenuProperties* menu_prop, const Controls* controls);

  void Update(const int key);
};