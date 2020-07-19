#include "Game.h"

Game::Game(const unsigned int seed)
    : player(Position(0, 0), Controls(TK_LEFT, TK_RIGHT, TK_UP, TK_DOWN), Sprite(TEXTURE_PLAYER, COLOR_WHITE),
             GameStats(), Type(0)),
      map_manager(seed, player.Get<Position>()),
      player_control(&player, &map_manager),
      screen(&map_manager, &player) {}

void Game::Run() {
  map_manager.TryGenerateChunk(map_manager.GetChunkCoords(player.Get<Position>()));
  while (true) {
    if (Input()) break;
    Update();
    Render();
  }
}

int Game::Input() {
  if (terminal_has_input()) {
    int key = terminal_read();
    if (key == TK_CLOSE) return 1;
    player_control.Update(key);
  }
  return 0;
}
// TODO: this something
void Game::Update() {}
void Game::Render() {
  screen.Update();
  screen.UpdateGUI();
}