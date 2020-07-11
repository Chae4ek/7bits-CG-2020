#pragma once

#include "Player.h"

#define SPRITE_PLAYER '@'
#define SPRITE_WALL '#'

class Screen
{
private:
	Player *player;
public:
	Screen(Player&);
	
	void Output();
};