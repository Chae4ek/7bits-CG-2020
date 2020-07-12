#pragma once

class Map
{
private:
	const unsigned int seed;
public:
	Map(unsigned int seed);
	
	constexpr unsigned int GetSeed();
	
	// Range of [0, 1]
	double PerlinNoise(double x, double y);
	double DotGradient(int, int, double, double);
	constexpr double Lerp(double, double, double);
};