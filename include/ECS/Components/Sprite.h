#pragma once

#include <BearLibTerminal.h>

#include "ECS/IComponent.h"

class Sprite : public IComponent {
 public:
  char texture;
  color_t color;

  int hex_texture;

  Sprite(const char texture, const color_t color, int hex_texture)
      : texture(texture), color(color), hex_texture(hex_texture) {}
};