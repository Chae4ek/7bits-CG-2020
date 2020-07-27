#pragma once

#include <BearLibTerminal.h>

#include <map>

#include "ECS/Components.h"

constexpr color_t _COLOR_RED = 0xFFFF0000;
constexpr color_t _COLOR_ORANGE = 0xFFFF7F00;
constexpr color_t _COLOR_YELLOW = 0xFFFFFF00;
constexpr color_t _COLOR_GREEN = 0xFF00FF00;
constexpr color_t _COLOR_AQUA = 0xFF00FFFF;
constexpr color_t _COLOR_BLUE = 0xFF3F42FF;
constexpr color_t _COLOR_PURPLE = 0xFFBF00FF;
constexpr color_t _COLOR_WHITE = 0xFFFFFFFF;
constexpr color_t _COLOR_GREY = 0xFF7F7F7F;

constexpr int TYPE_NULL = 0;
constexpr int TYPE_PLAYER = 1;
constexpr int TYPE_COIN = 2;
constexpr int TYPE_WALL = 3;
constexpr int TYPE_EXIT = 4;

const std::map<int, Sprite> PREFABS = {{TYPE_NULL, Sprite('x', _COLOR_RED)},
                                       {TYPE_PLAYER, Sprite('@', _COLOR_WHITE)},
                                       {TYPE_COIN, Sprite('$', _COLOR_YELLOW)},
                                       {TYPE_WALL, Sprite('#', _COLOR_GREY)},
                                       {TYPE_EXIT, Sprite('>', _COLOR_AQUA)}};

static uint32_t _SEED_RANDOM = 1;

static int Random() {
  _SEED_RANDOM = 214013 * _SEED_RANDOM + 2531011;
  return static_cast<unsigned int>(_SEED_RANDOM / 65536) % 32768;
}
static constexpr void Srand(const unsigned int seed) {
  _SEED_RANDOM = seed;
}
static inline void Srand(const unsigned int seed, const int seed1, const int seed2) {
  Srand(seed);
  Srand(seed1 + Random());
  Srand(seed2 + Random());
}