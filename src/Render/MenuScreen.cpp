#include "Render/MenuScreen.h"

MenuScreen::MenuScreen(const MenuProperties* menu_prop) : menu_prop(menu_prop) {}

void MenuScreen::Update() const {
  terminal_clear();

  Print(COLOR_YELLOW, 1, 1, "Меню");

  Print(COLOR_AQUA, 1, 3 + menu_prop->cursor * 2, ">");

  Print(COLOR_WHITE, 3, 3, "new_graphics: %s", menu_prop->new_graphics ? "true" : "false");
  Print(COLOR_WHITE, 3, 5, "coming soon...");

  terminal_refresh();
}