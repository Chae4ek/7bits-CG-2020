#pragma once

#include <BearLibTerminal.h>

#include "ECS/Components/Controls.h"
#include "ECS/Components/MenuProperties.h"
#include "Tools/Localization.h"

class MenuControl {
 private:
  MenuProperties* menu_prop;
  const Controls* controls;
  Localization* localization;

 public:
  explicit MenuControl(MenuProperties* menu_prop, const Controls* controls, Localization* localization);

  void Update(const int key);

  void SetNewGraphics() const;
  void SetOldGraphics() const;
};