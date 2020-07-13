#pragma once

static unsigned long int _SEED_RANDOM = 1;

int Random()
{
	_SEED_RANDOM = 214013 * _SEED_RANDOM + 2531011;
	return static_cast<unsigned int>(_SEED_RANDOM / 65536) % 32768;
}
void SSrand(unsigned int seed, int seed1, int seed2)
{
	_SEED_RANDOM = seed;
	_SEED_RANDOM = seed1 + Random();
	_SEED_RANDOM = seed2 + Random();
}