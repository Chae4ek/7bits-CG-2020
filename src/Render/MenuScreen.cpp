#include "Render/MenuScreen.h"

MenuScreen::MenuScreen(const MenuProperties* menu_prop) : menu_prop(menu_prop) {}

void MenuScreen::Update() const {
  terminal_clear();

  Print(COLOR_YELLOW, 1, 1, "Menu");

  Print(COLOR_AQUA, 1, 3 + menu_prop->cursor * 2, ">");

  Print(COLOR_WHITE, 3, 3, "Play");
  Print(COLOR_WHITE, 3, 5, "New graphics: %s", menu_prop->new_graphics ? "On" : "Off");
  Print(COLOR_WHITE, 3, 7, "Exit");

  terminal_refresh();
}