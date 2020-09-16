#pragma once

#include "Tools/MapManager.h"

class IScreen {
 protected:
  const int pos_game_x = 11;
  const int pos_game_y = 4;

  inline void Print(int x, int y, const Sprite *sprite, const bool new_graphics) const {
    terminal_color(sprite->color);
    if (new_graphics)
      terminal_put(x, y, sprite->hex_texture);
    else
      terminal_put(x, y, sprite->texture);
  }
  template<class... Args>
  inline void Print(color_t color, int x, int y, const char *s, Args... args) const {
    terminal_color(color);
    terminal_printf(x, y, s, args...);
  }

 public:
  virtual void Update() const = 0;
};