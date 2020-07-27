#include <BearLibTerminal.h>

#include <iostream>
#include <string>

#include "Advanced.h"
#include "Tools/ReaderStruct.h"

int main() {
  std::cout << std::endl << "Structure name: ";
  std::string name;
  getline(std::cin, name);
  std::string struct_path = "./Structures/" + name;

  terminal_open();

  terminal_set("window: title=Game, size=80x30; input: mouse-cursor=true, filter=[keyboard, mouse+]");
  terminal_composition(TK_ON);

  const int WIDTH = terminal_state(TK_WIDTH);
  const int HEIGHT = terminal_state(TK_HEIGHT) - 6;

  int **structure = new int *[WIDTH];
  for (int i = 0; i < WIDTH; ++i) {
    structure[i] = new int[HEIGHT];
    for (int j = 0; j < HEIGHT; ++j) structure[i][j] = TYPE_NULL;
  }

  std::map<std::pair<int, int>, int> level_exit;

  int current_type = 0;
  int x = 0;
  int y = 0;

  int x_top = 0;
  int y_top = 0;
  int x_bot;
  int y_bot;

  FILE *file = fopen(struct_path.c_str(), "rb");
  ReaderStruct reader(0, 0);
  bool generate = reader.SetStruct(file);
  struct_info info = reader.GetInfo();

  if (generate) {
    for (; info.x_top <= info.x_bot; ++info.x_top)
      for (int y = info.y_top; y <= info.y_bot; ++y) {
        int type = reader.GetNext();
        structure[info.x_top][y] = type;

        if (type == TYPE_EXIT) level_exit[std::make_pair(info.x_top, y)] = reader.GetNext();
      }
  }
  if (file) fclose(file);

  int set = 0;

  while (true) {
    terminal_refresh();
    terminal_clear();

    for (int x = 0; x < WIDTH; ++x) {
      for (int y = 0; y < HEIGHT; ++y) {
        if (structure[x][y] != TYPE_NULL) {
          terminal_color(PREFABS.at(structure[x][y]).color);
          terminal_put(x, y, PREFABS.at(structure[x][y]).texture);
        }
      }
      terminal_color(_COLOR_BLUE);
      terminal_put(x, HEIGHT, PREFABS.at(TYPE_WALL).texture);
    }
    terminal_color(_COLOR_YELLOW);
    terminal_printf(1, HEIGHT + 2, "[[WHEEL]] listing types");
    terminal_printf(1, HEIGHT + 4, "[[LCM/RCM]] set/delete type");

    terminal_color(PREFABS.at(current_type).color);
    terminal_put(x, y, PREFABS.at(current_type).texture);

    if (terminal_has_input()) {
      int key = terminal_read();

      if (key == TK_CLOSE) break;

      if (key == TK_MOUSE_LEFT) set = 1;
      if (key == TK_MOUSE_RIGHT) set = -1;
      if (key == (TK_MOUSE_LEFT | TK_KEY_RELEASED) || key == (TK_MOUSE_RIGHT | TK_KEY_RELEASED)) set = 0;

      if (key == TK_MOUSE_MOVE) {
        x = terminal_state(TK_MOUSE_X);
        y = terminal_state(TK_MOUSE_Y);
      }
      if (key == TK_MOUSE_SCROLL) {
        int amount = terminal_state(TK_MOUSE_WHEEL);

        current_type += amount;
        if (current_type < 0) current_type = 0;
        if (current_type >= PREFABS.size()) current_type = PREFABS.size() - 1;
      }
    }
    if (set == 1) {
      structure[x][y] = current_type;
      if (current_type == TYPE_EXIT) {
        std::cout << std::endl << "level id: ";
        std::cin >> level_exit[std::make_pair(x, y)];
        set = 0;
      }
    } else if (set == -1)
      structure[x][y] = 0;
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

  int size_x = x_bot - x_top;
  int size_y = y_bot - y_top;

  terminal_close();

  std::cout << std::endl << "Save as: ";
  std::cin >> name;
  struct_path = "./Structures/" + name;

  FILE *f = fopen(struct_path.c_str(), "wb");
  fwrite(&size_x, sizeof(int), 1, f);
  fwrite(&size_y, sizeof(int), 1, f);

  for (; x_top <= x_bot; ++x_top)
    for (int y = y_top; y <= y_bot; ++y) {
      int type = structure[x_top][y];
      fwrite(&type, sizeof(int), 1, f);

      if (type == TYPE_EXIT) fwrite(&level_exit.at(std::make_pair(x_top, y)), sizeof(int), 1, f);
    }

  fclose(f);

  for (int i = 0; i < WIDTH; ++i) delete[] structure[i];
  delete[] structure;

  level_exit.clear();

  return 0;
}