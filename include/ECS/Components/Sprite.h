#pragma once

#include <BearLibTerminal.h>

#include "ECS/IComponent.h"

// TODO: mixed textures and colors
class Sprite : public IComponent {
 public:
  char texture;
  color_t color;

  Sprite(const char texture, const color_t color) : texture(texture), color(color) {}
};