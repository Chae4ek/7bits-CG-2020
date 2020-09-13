#include "Game.h"

int main() {
  terminal_open();
  terminal_refresh();

  // TODO: resizeable window with resize object sprites
  terminal_set("window: title=Game, size=105x34; input: filter=[keyboard, mouse]");
  terminal_composition(TK_ON);

  Game game(0);

  game.Run();

  terminal_close();
  return 0;
}