#pragma once

static unsigned long int _SEED_RANDOM = 1;

int Random()
{
	_SEED_RANDOM = 214013 * _SEED_RANDOM + 2531011;
	return static_cast<unsigned int>(_SEED_RANDOM / 65536) % 32768;
}
constexpr void Srand(unsigned int seed)
{
	_SEED_RANDOM = seed;
}
void Srand(unsigned int seed, int seed1, int seed2)
{
	Srand(seed);
	Srand(seed1 + Random());
	Srand(seed2 + Random());
}