#pragma once

#include "IComponent.h"

class Position : public IComponent {
 public:
  int pos_x;
  int pos_y;

  Position(int x, int y) : pos_x(x), pos_y(y) {}
};

class Controls : public IComponent {
 public:
  int KEY_LEFT;
  int KEY_RIGHT;
  int KEY_UP;
  int KEY_DOWN;

  Controls(int KEY_LEFT, int KEY_RIGHT, int KEY_UP, int KEY_DOWN)
      : KEY_LEFT(KEY_LEFT), KEY_RIGHT(KEY_RIGHT), KEY_UP(KEY_UP), KEY_DOWN(KEY_DOWN) {}
};

// TODO: mixed textures and colors
class Sprite : public IComponent {
 public:
  char texture;
  color_t color;

  Sprite(char texture, color_t color) : texture(texture), color(color) {}
};

class GameStats : public IComponent {
 public:
  int coins = 0;
  int step_count = 0;
};

class Type : public IComponent {
 public:
  const int type;

  explicit Type(const int type) : type(type) {}
};