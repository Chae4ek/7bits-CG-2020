#include <BearLibTerminal.h>

#include "Advanced.h"
#include "ECS/Components.h"
#include "ECS/Entity.h"

int main() {
  terminal_open();

  terminal_set("window: title=Game, size=80x30");

  const int WIDTH = terminal_state(TK_WIDTH);
  const int HEIGHT = terminal_state(TK_HEIGHT) - 6;

  int **structure = new int *[WIDTH];
  for (int i = 0; i < WIDTH; ++i) {
    structure[i] = new int[HEIGHT];
    for (int j = 0; j < HEIGHT; ++j) structure[i][j] = TYPE_NULL;
  }

  // TODO: replace with expandable structure
  const int max = 4;
  Sprite entities[4] = {Sprite('x', _COLOR_RED), Sprite(TEXTURE_PLAYER, COLOR_PLAYER), Sprite(TEXTURE_COIN, COLOR_COIN),
                        Sprite(TEXTURE_WALL, COLOR_WALL)};

  int current_type = 0;
  int x = 0;
  int y = 0;

  int x_top;
  int y_top;
  int x_bot;
  int y_bot;

  FILE *f = fopen("Structures/new", "r");
  if (f) {
    fread(&x_top, sizeof(int), 1, f);
    fread(&y_top, sizeof(int), 1, f);
    fread(&x_bot, sizeof(int), 1, f);
    fread(&y_bot, sizeof(int), 1, f);

    for (; x_top <= x_bot; ++x_top)
      for (int y = y_top; y <= y_bot; ++y) fread(&structure[x_top][y], sizeof(int), 1, f);

    fclose(f);
  }

  while (true) {
    terminal_refresh();
    terminal_clear();

    for (int x = 0; x < WIDTH; ++x) {
      for (int y = 0; y < HEIGHT; ++y) {
        if (structure[x][y]) {
          terminal_color(entities[structure[x][y]].color);
          terminal_put(x, y, entities[structure[x][y]].texture);
        }
      }
      terminal_color(_COLOR_BLUE);
      terminal_put(x, HEIGHT, TEXTURE_WALL);
    }
    terminal_color(_COLOR_YELLOW);
    terminal_printf(1, HEIGHT + 2, "[[Q/W]] listing types");

    terminal_color(entities[current_type].color);
    terminal_put(x, y, entities[current_type].texture);

    if (terminal_has_input()) {
      int key = terminal_read();

      if (key == TK_CLOSE) break;

      if (key == TK_ENTER) structure[x][y] = current_type;

      if (key == TK_LEFT && x > 0) --x;
      if (key == TK_RIGHT && x < WIDTH - 1) ++x;
      if (key == TK_UP && y > 0) --y;
      if (key == TK_DOWN && y < HEIGHT - 1) ++y;

      if (key == TK_Q && current_type > 0) --current_type;
      if (key == TK_W && current_type < max - 1) ++current_type;
    }
  }

  x_top = WIDTH;
  y_top = HEIGHT;
  x_bot = 0;
  y_bot = 0;

  for (int x = 0; x < WIDTH; ++x)
    for (int y = 0; y < HEIGHT; ++y)
      if (structure[x][y] != TYPE_NULL) {
        if (x < x_top) x_top = x;
        if (y < y_top) y_top = y;
        if (x > x_bot) x_bot = x;
        if (y > y_bot) y_bot = y;
      }

  f = fopen("Structures/new", "w");
  fwrite(&x_top, sizeof(int), 1, f);
  fwrite(&y_top, sizeof(int), 1, f);
  fwrite(&x_bot, sizeof(int), 1, f);
  fwrite(&y_bot, sizeof(int), 1, f);

  for (; x_top <= x_bot; ++x_top)
    for (int y = y_top; y <= y_bot; ++y) fwrite(&structure[x_top][y], sizeof(int), 1, f);

  fclose(f);

  for (int i = 0; i < WIDTH; ++i) delete[] structure[i];
  delete[] structure;

  terminal_close();
  return 0;
}