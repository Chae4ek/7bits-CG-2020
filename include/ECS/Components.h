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

class Sprite : public IComponent
{
public:
	char sprite;
	
	Sprite(char sprite) : sprite(sprite) {}
};