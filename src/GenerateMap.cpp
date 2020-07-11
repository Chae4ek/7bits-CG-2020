#include <stdlib.h>
#include "GenerateMap.h"

Map::Map(long long seed) : seed(seed) {}

constexpr double Lerp(double, double, double);

double Map::PerlinNoise(double x, double y)
{
	int x0 = static_cast<int>(x);
	int y0 = static_cast<int>(y);
	int x1 = x0 + 1;
	int y1 = y0 + 1;
	
	double tx = x - static_cast<double>(x0);
	double ty = y - static_cast<double>(y0);
	
	double d0, d1, i0, i1;
	
	d0 = DotGrad(x0, y0, x, y);
	d1 = DotGrad(x1, y0, x, y);
	i0 = Lerp(d0, d1, tx);
	
	d0 = DotGrad(x0, y1, x, y);
	d1 = DotGrad(x1, y1, x, y);
	i1 = Lerp(d0, d1, tx);
	
	double noise = Lerp(i0, i1, ty);
	if (noise < 0) noise *= -1;
	return noise;
}
double Map::DotGrad(int rand_x, int rand_y, double x, double y)
{
	srand(seed);
	srand(rand_x + rand());
	srand(rand_y + rand());
	int r = rand() % 4;
	double r1, r2;
	if (r == 0) r1 = 0, r2 = 1;
	else if (r == 1) r1 = 0, r2 = -1;
	else if (r == 2) r1 = 1, r2 = 0;
	else r1 = -1, r2 = 0;
	
	x -= static_cast<double>(rand_x);
	y -= static_cast<double>(rand_y);
	
	return x * r1 + y * r2;
}
constexpr double Lerp(double a, double b, double t)
{
	return a + (b - a) * t;
}