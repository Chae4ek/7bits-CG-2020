#pragma once

#include "Component.h"

class Position : public IComponent
{
public:
	int pos_x;
	int pos_y;
	
	Position(int x, int y) : pos_x(x), pos_y(y) {}
};

class Movement : public IComponent
{
public:
	int KEY_LEFT;
	int KEY_RIGHT;
	int KEY_UP;
	int KEY_DOWN;
	
	Movement(int KEY_LEFT, int KEY_RIGHT, int KEY_UP, int KEY_DOWN) :
		KEY_LEFT(KEY_LEFT),
		KEY_RIGHT(KEY_RIGHT),
		KEY_UP(KEY_UP),
		KEY_DOWN(KEY_DOWN) {}
};

#define COLOR_RED 0xFFFF0000
#define COLOR_ORANGE 0xFFFF7F00
#define COLOR_YELLOW 0xFFFFFF00
#define COLOR_GREEN 0xFF00FF00
#define COLOR_AQUA 0xFF00FFFF
#define COLOR_BLUE 0xFF3F42FF
#define COLOR_PURPLE 0xFFBF00FF
#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_GREY 0xFF7F7F7F

// TODO: mixed textures and colors
class Sprite : public IComponent
{
public:
	char texture;
	color_t color;
	
	Sprite(char texture, color_t color) : texture(texture), color(color) {}
};