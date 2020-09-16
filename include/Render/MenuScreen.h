#pragma once

#include "ECS/Components/MenuProperties.h"
#include "IScreen.h"
#include "Tools/Localization.h"

class MenuScreen : protected IScreen {
 private:
  const MenuProperties* menu_prop;
  const Localization* localization;

 public:
  MenuScreen(const MenuProperties* menu_prop, const Localization* localization);

  void Update() const;
};