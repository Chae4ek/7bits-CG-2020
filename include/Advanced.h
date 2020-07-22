#pragma once

#include <BearLibTerminal.h>

#include <utility>

constexpr color_t _COLOR_RED = 0xFFFF0000;
constexpr color_t _COLOR_ORANGE = 0xFFFF7F00;
constexpr color_t _COLOR_YELLOW = 0xFFFFFF00;
constexpr color_t _COLOR_GREEN = 0xFF00FF00;
constexpr color_t _COLOR_AQUA = 0xFF00FFFF;
constexpr color_t _COLOR_BLUE = 0xFF3F42FF;
constexpr color_t _COLOR_PURPLE = 0xFFBF00FF;
constexpr color_t _COLOR_WHITE = 0xFFFFFFFF;
constexpr color_t _COLOR_GREY = 0xFF7F7F7F;

// TODO: create dictionary for all
// make prefabs for entities

constexpr int TYPE_NULL = 0;
constexpr int TYPE_PLAYER = 1;
constexpr int TYPE_COIN = 2;
constexpr int TYPE_WALL = 3;

constexpr char TEXTURE_PLAYER = '@';
constexpr char TEXTURE_COIN = '$';
constexpr char TEXTURE_WALL = '#';

constexpr color_t COLOR_PLAYER = _COLOR_WHITE;
constexpr color_t COLOR_COIN = _COLOR_YELLOW;
constexpr color_t COLOR_WALL = _COLOR_GREY;

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