#pragma once

#include "ECS/Components/MenuProperties.h"
#include "IScreen.h"

class MenuScreen : protected IScreen {
 private:
  const MenuProperties* menu_prop;

 public:
  explicit MenuScreen(const MenuProperties* menu_prop);

  void Update() const;
};