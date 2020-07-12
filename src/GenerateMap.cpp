#include "GenerateMap.h"
#include "Advanced.h"

Map::Map(unsigned int seed) : seed(seed) {}

unsigned int Map::GetSeed() { return seed; }

bool Map::isWall(int x, int y)
{
	double noise = PerlinNoise(x / smooth, y / smooth);
	SSrand(seed, x, y);
	if ((noise > threshold + sharp || Random() % 2) && ((noise > threshold - sharp && Random() % 2) || noise > threshold))
		return true;
	return false;
}
double Map::PerlinNoise(double x, double y)
{
	int x0 = static_cast<int>(x);
	int y0 = static_cast<int>(y);
	int x1 = x0 + 1;
	int y1 = y0 + 1;
	
	double tx = x - x0;
	double d1, d2, lerp_x_top, lerp_x_bottom;
	
	d1 = DotGradient(x0, y0, x, y);
	d2 = DotGradient(x1, y0, x, y);
	lerp_x_top = Lerp(d1, d2, tx);
	
	d1 = DotGradient(x0, y1, x, y);
	d2 = DotGradient(x1, y1, x, y);
	lerp_x_bottom = Lerp(d1, d2, tx);
	
	double lerp_xy = Lerp(lerp_x_top, lerp_x_bottom, y - y0);
	if (lerp_xy < 0) lerp_xy *= -1;
	return lerp_xy;
}
double Map::DotGradient(int rand_x, int rand_y, double x, double y)
{
	SSrand(seed, rand_x, rand_y);
	
	int r = Random() % 4;
	x -= rand_x;
	y -= rand_y;
	
	if (r == 0) rand_x = 0, rand_y = 1;
	else if (r == 1) rand_x = 0, rand_y = -1;
	else if (r == 2) rand_x = 1, rand_y = 0;
	else rand_x = -1, rand_y = 0;
	
	return x * rand_x + y * rand_y;
}
constexpr double Map::Lerp(double a, double b, double t)
{
	t = t * t * t * (t * (t * 6 - 15) + 10);
	return a + (b - a) * t;
}