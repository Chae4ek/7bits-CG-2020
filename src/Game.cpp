#include "Game.h"

Game::Game(const unsigned int start_seed)
    : menu_prop(MenuProperties(true, false)),
      player(Position(0, 0),
             Controls(TK_LEFT, TK_RIGHT, TK_UP, TK_DOWN, TK_ENTER, TK_ESCAPE, TK_1, TK_2, TK_3, TK_4, TK_5, TK_6, TK_7,
                      TK_8),
             Sprite(PREFABS.at(TYPE_PLAYER).texture, PREFABS.at(TYPE_PLAYER).color), GameStats(), Type(TYPE_PLAYER),
             Defense(10, 5), Inventory(8)),
      map_manager(start_seed, player.Get<Position>()),
      player_control(&player, &map_manager),
      level_exit_control(&player, &map_manager),
      menu_control(&menu_prop, player.Get<Controls>()),
      game_screen(&map_manager, &player),
      gui_screen(&map_manager, &player),
      level_exit_screen(player.Get<GameStats>()),
      menu_screen(&menu_prop) {}

void Game::Run() {
  // TODO: delete dynamic generation?

  // due to dynamic generation,
  // DIFFERENT structures are possible even with SAME SEEDS (if structs will generate on several chunks)
  // and it can create bugs

  // it fully fixed now
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
// TODO: this something
void Game::Update() {}
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