#pragma once

#include "MapManager.h"

static unsigned long int _SEED_RANDOM = 1;

static int Random()
{
	_SEED_RANDOM = 214013 * _SEED_RANDOM + 2531011;
	return static_cast<unsigned int>(_SEED_RANDOM / 65536) % 32768;
}
static constexpr void Srand(unsigned int seed)
{
	_SEED_RANDOM = seed;
}
static inline void Srand(unsigned int seed, int seed1, int seed2)
{
	Srand(seed);
	Srand(seed1 + Random());
	Srand(seed2 + Random());
}

static constexpr std::pair<int, int> GlobalToLocal(MapManager *mm, int x, int y)
{
	int xl = x % mm->size_x;
	int yl = y % mm->size_y;
	if (xl < 0) xl += mm->size_x;
	if (yl < 0) yl += mm->size_y;
	return std::make_pair(xl, yl);
}