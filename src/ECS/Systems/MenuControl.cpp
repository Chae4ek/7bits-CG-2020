#include "ECS/Systems/MenuControl.h"

MenuControl::MenuControl(MenuProperties* menu_prop, const Controls* controls, Localization* localization)
    : menu_prop(menu_prop), controls(controls), localization(localization) {}

void MenuControl::Update(const int key) {
  if (key == controls->KEY_ESC) {
    menu_prop->in_menu = !menu_prop->in_menu;
    menu_prop->cursor = 0;
  }
  if (!menu_prop->in_menu) return;

  if (key == controls->KEY_UP && menu_prop->cursor > 0) --menu_prop->cursor;
  if (key == controls->KEY_DOWN && menu_prop->cursor < 3) ++menu_prop->cursor;

  if (key == controls->KEY_ENTER) {
    switch (menu_prop->cursor) {
      case 0:
        menu_prop->in_menu = !menu_prop->in_menu;
        menu_prop->cursor = 0;
        break;
      case 1:
        menu_prop->new_graphics = !menu_prop->new_graphics;
        if (menu_prop->new_graphics)
          SetNewGraphics();
        else
          SetOldGraphics();
        break;
      case 2:
        menu_prop->local_id++;
        if (menu_prop->local_id >= static_cast<int>(menu_prop->locals.size())) menu_prop->local_id = 0;
        localization->SetLocal(menu_prop->locals.at(menu_prop->local_id));
        break;
      case 3:
        menu_prop->exit = true;
        break;
      default:
        break;
    }
  }
}

void MenuControl::SetNewGraphics() const {
  terminal_set("window: cellsize=12x12");
}
void MenuControl::SetOldGraphics() const {
  terminal_set("window: cellsize=auto");
}