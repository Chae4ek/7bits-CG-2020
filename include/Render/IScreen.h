#pragma once

#include "Tools/MapManager.h"

class IScreen {
 protected:
  const int pos_game_x = 10;
  const int pos_game_y = 4;

  inline void Print(int x, int y, const Sprite *sprite) const {
    terminal_color(sprite->color);
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