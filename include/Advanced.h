#pragma once

#include <utility>

#include "MapManager.h"

// TODO: const or define?
#define COLOR_RED 0xFFFF0000
#define COLOR_ORANGE 0xFFFF7F00
#define COLOR_YELLOW 0xFFFFFF00
#define COLOR_GREEN 0xFF00FF00
#define COLOR_AQUA 0xFF00FFFF
#define COLOR_BLUE 0xFF3F42FF
#define COLOR_PURPLE 0xFFBF00FF
#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_GREY 0xFF7F7F7F

#define TYPE_COIN 1

static uint32_t _SEED_RANDOM = 1;

static int Random() {
  _SEED_RANDOM = 214013 * _SEED_RANDOM + 2531011;
  return static_cast<unsigned int>(_SEED_RANDOM / 65536) % 32768;
}
static constexpr void Srand(unsigned int seed) {
  _SEED_RANDOM = seed;
}
static inline void Srand(unsigned int seed, int seed1, int seed2) {
  Srand(seed);
  Srand(seed1 + Random());
  Srand(seed2 + Random());
}

static constexpr std::pair<int, int> GlobalToLocal(const MapManager *mm, int x, int y) {
  int xl = x % mm->size_x;
  int yl = y % mm->size_y;
  if (xl < 0) xl += mm->size_x;
  if (yl < 0) yl += mm->size_y;
  return std::make_pair(xl, yl);
}