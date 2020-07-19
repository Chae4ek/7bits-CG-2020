#include "Game.h"

int main() {
  terminal_open();
  terminal_refresh();

  // TODO: resizeable window with resize object sprites
  terminal_set("window: title=Game, size=80x30");

  Game game(1);

  game.Run();

  terminal_close();
  return 0;
}