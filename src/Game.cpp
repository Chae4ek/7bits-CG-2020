#include "Game.h"

Game::Game(const unsigned int seed)
    : player(Position(0, 0), Controls(TK_LEFT, TK_RIGHT, TK_UP, TK_DOWN), PREFABS.at(TYPE_PLAYER), GameStats(),
             Type(0)),
      map_manager(seed, player.Get<Position>()),
      player_control(&player, &map_manager),
      screen(&map_manager, &player) {}

void Game::Run() {
  // TODO: delete dynamic generation?

  // due to dynamic generation,
  // DIFFERENT structures are possible even with SAME SEEDS (if structs will generate on several chunks)
  // and it can create bugs

  // it fully fixed now
  Generate(&map_manager).TryGenerateChunk(map_manager.GetChunkCoords(player.Get<Position>()), "-hub");

  while (true) {
    if (Input()) break;
    if (!map_manager.level_exit) {
      Update();
      Render();
    } else {
      UpdateLevelExit();
    }
  }
}

int Game::Input() {
  if (terminal_has_input()) {
    int key = terminal_read();
    if (key == TK_CLOSE) return 1;

    if (!map_manager.level_exit)
      player_control.Update(key);
    else
      InputLevelExit(key);
  }
  return 0;
}
// TODO: this something
void Game::Update() {}
void Game::Render() {
  screen.Update();
  screen.UpdateGUI();
}

void Game::InputLevelExit(const int key) {
  if (key == TK_ENTER) {
    map_manager.level_exit = false;
    Generate(&map_manager).TryGenerateChunk(map_manager.GetChunkCoords(player.Get<Position>()));
  }
}
void Game::UpdateLevelExit() {
  screen.UpdateLevelExit();
}