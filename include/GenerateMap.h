#pragma once

class Map
{
private:
	const long long seed;
public:
	Map(long long seed);
	
	double PerlinNoise(double x, double y);
	double DotGrad(int, int, double, double);
};