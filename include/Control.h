#pragma once

#include <BearLibTerminal.h>
#include "Player.h"

#define KEY_LEFT TK_LEFT
#define KEY_RIGHT TK_RIGHT
#define KEY_UP TK_UP
#define KEY_DOWN TK_DOWN

class Control
{
private:
    Player *player;
public:
    Control(Player&);
    
    void Check(int);
};