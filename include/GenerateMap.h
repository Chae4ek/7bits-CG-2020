#pragma once

class Map
{
private:
	const unsigned int seed;
public:
	// For debug
	// TODO: private this later
	double smooth = 60;
	double threshold = 0.125;
	double sharp = 0.009;
	
	Map(unsigned int seed);
	
	unsigned int GetSeed();
	
	bool isWall(int x, int y);
	// Range of [0, 1]
	double PerlinNoise(double x, double y);
	double DotGradient(int, int, double, double);
	constexpr double Lerp(double, double, double);
};