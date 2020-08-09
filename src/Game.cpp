#include "Game.h"

Game::Game(const unsigned int start_seed)
    : player(Position(0, 0), Controls(TK_LEFT, TK_RIGHT, TK_UP, TK_DOWN, TK_ENTER), PREFABS.at(TYPE_PLAYER),
             GameStats(), Type(TYPE_PLAYER)),
      map_manager(start_seed, player.Get<Position>()),
      player_control(&player, &map_manager),
      level_exit_control(&player, &map_manager),
      game_screen(&map_manager, &player),
      gui_screen(&map_manager, player.Get<GameStats>()),
      level_exit_screen(player.Get<GameStats>()) {}

void Game::Run() {
  // TODO: delete dynamic generation?

  // due to dynamic generation,
  // DIFFERENT structures are possible even with SAME SEEDS (if structs will generate on several chunks)
  // and it can create bugs

  // it fully fixed now
  Generate(&map_manager, player.Get<Position>()).TryGenerateChunk(map_manager.GetChunkCoords(player.Get<Position>()));

  while (true) {
    if (Input()) break;
    if (!map_manager.level_exit) {
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

    player_control.Update(key);
    level_exit_control.Update(key);
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