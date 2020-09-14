#include "Game.h"

Game::Game(const unsigned int start_seed)
    : localization("en.txt"),
      menu_prop(MenuProperties(true, false, {"en.txt", "ru.txt"})),
      player(
          Position(0, 0),
          Controls(TK_LEFT, TK_RIGHT, TK_UP, TK_DOWN, TK_ENTER, TK_ESCAPE, TK_1, TK_2, TK_3, TK_4, TK_5, TK_6, TK_7,
                   TK_8),
          Sprite(PREFABS.at(TYPE_PLAYER).texture, PREFABS.at(TYPE_PLAYER).color, PREFABS.at(TYPE_PLAYER).hex_texture),
          GameStats(), Type(TYPE_PLAYER), Defense(10, 20), Inventory(8)),
      map_manager(start_seed, &player),
      player_control(&player, &map_manager),
      level_exit_control(&player, &map_manager),
      menu_control(&menu_prop, player.Get<Controls>(), &localization),
      game_screen(&map_manager, &player, &menu_prop),
      gui_screen(&map_manager, &player, &menu_prop, &localization),
      level_exit_screen(player.Get<GameStats>(), &localization),
      menu_screen(&menu_prop, &localization),
      enemy_control(&player, &map_manager) {
  terminal_set("0x1001: ./Textures/@.png, size=10x10, align=center");
  terminal_set("0x1002: ./Textures/$.png, size=4x4, align=center");
  terminal_set("0x1003: ./Textures/#.png, size=12x12, align=center");
  terminal_set("0x1004: ./Textures/door.png, size=10x10, align=center");
  terminal_set("0x1005: ./Textures/i.png, size=12x12, align=center");
  terminal_set("0x1006: ./Textures/o.png, size=12x12, align=center");
  terminal_set("0x1007: ./Textures/X.png, size=10x10, align=center");
  terminal_set("0x1008: ./Textures/E.png, size=10x10, align=center");
}

void Game::Run() {
  Generate(&map_manager, player.Get<Position>()).TryGenerateChunk(map_manager.GetChunkCoords(player.Get<Position>()));

  while (true) {
    if (Input()) break;
    if (menu_prop.in_menu) {
      RenderMenu();
    } else if (!map_manager.level_exit) {
      Update();
      Render();
    } else {
      RenderLevelExit();
    }
  }
}

int Game::Input() {
  if (terminal_has_input()) {
    const int key = terminal_read();
    if (key == TK_CLOSE) return 1;

    if (!menu_prop.in_menu) {
      player_control.Update(key);
      level_exit_control.Update(key);
    }
    menu_control.Update(key);
    if (menu_prop.exit) return 1;
  }
  return 0;
}
void Game::Update() {
  enemy_control.Update();
}
void Game::Render() const {
  game_screen.Update();
  gui_screen.Update();
}

void Game::RenderLevelExit() const {
  level_exit_screen.Update();
}

void Game::RenderMenu() const {
  menu_screen.Update();
}