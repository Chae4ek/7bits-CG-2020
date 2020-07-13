#pragma once

#include "Component.h"

class Position : public IComponent
{
public:
	int pos_x;
	int pos_y;
	
	Position(int x, int y) : pos_x(x), pos_y(y) {}
};

// TODO: delete this later
class Test : public IComponent
{
public:
	int t;
	
	Test(int t) : t(t) {}
};