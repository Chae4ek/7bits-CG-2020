#include "ECS/Systems/MenuControl.h"

MenuControl::MenuControl(MenuProperties* menu_prop, const Controls* controls)
    : menu_prop(menu_prop), controls(controls) {}

void MenuControl::Update(const int key) {
  if (key == controls->KEY_ESC) {
    menu_prop->in_menu = !menu_prop->in_menu;
    menu_prop->cursor = 0;
  }
  if (!menu_prop->in_menu) return;

  if (key == controls->KEY_UP && menu_prop->cursor > 0) --menu_prop->cursor;
  if (key == controls->KEY_DOWN && menu_prop->cursor < 2) ++menu_prop->cursor;

  // TODO: replace to dictionary
  if (key == controls->KEY_ENTER) {
    if (menu_prop->cursor == 0) {
      menu_prop->in_menu = !menu_prop->in_menu;
      menu_prop->cursor = 0;
    }
    if (menu_prop->cursor == 1) menu_prop->new_graphics = !menu_prop->new_graphics;
    if (menu_prop->cursor == 2) menu_prop->exit = true;
  }
}