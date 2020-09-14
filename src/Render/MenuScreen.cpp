#include "Render/MenuScreen.h"

MenuScreen::MenuScreen(const MenuProperties* menu_prop, const Localization* localization)
    : menu_prop(menu_prop), localization(localization) {}

void MenuScreen::Update() const {
  terminal_clear();

  Print(COLOR_YELLOW, 1, 1, "%s", localization->local.at("menu").c_str());

  Print(COLOR_AQUA, 1, 3 + menu_prop->cursor * 2, ">");

  Print(COLOR_WHITE, 3, 3, "%s", localization->local.at("play").c_str());
  Print(COLOR_WHITE, 3, 5, "%s: %s", localization->local.at("new_graphics").c_str(),
        menu_prop->new_graphics ? localization->local.at("on").c_str() : localization->local.at("off").c_str());
  Print(COLOR_WHITE, 3, 7, "%s: %s", localization->local.at("localization").c_str(),
        localization->local.at("language").c_str());
  Print(COLOR_WHITE, 3, 9, "%s", localization->local.at("exit").c_str());

  terminal_refresh();
}