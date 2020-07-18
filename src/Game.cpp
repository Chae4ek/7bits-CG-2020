#include "Game.h"

Game::Game()
    : player(Entity(Position(0, 0), Controls(TK_LEFT, TK_RIGHT, TK_UP, TK_DOWN), Sprite(TEXTURE_PLAYER, COLOR_WHITE),
                    GameStats(), Type(0))),
      wall_sprite(Sprite(TEXTURE_WALL, COLOR_GREY)),
      map_manager(MapManager(player.Get<Position>())),
      player_control(PlayerControl(player)),
      generate_map(GenerateMap(1, &map_manager)),
      collision(Collision(&map_manager, player)),
      screen(Screen(map_manager, player, wall_sprite)) {}

void Game::Run() {
  while (true) {
    Clear();
    if (Input()) break;
    Update();
    Render();
  }
}

// TODO: clear Event queue
void Game::Clear() {}
int Game::Input() {
  if (terminal_has_input()) {
    int key = terminal_read();
    if (key == TK_CLOSE) return 1;
    player_control.Update(key);
  }
  return 0;
}
void Game::Update() {
  generate_map.Update();
  collision.Update();
}
void Game::Render() {
  screen.Update();
  screen.UpdateGUI();
}