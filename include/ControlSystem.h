#pragma once

#include <BearLibTerminal.h>
#include "Player.h"

#define KEY_LEFT TK_LEFT
#define KEY_RIGHT TK_RIGHT
#define KEY_UP TK_UP
#define KEY_DOWN TK_DOWN

class Controls
{
private:
	Player *player;
public:
	Controls(Player&);
	
	void Check(int);
};