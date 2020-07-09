#pragma once

#include "Player.h"

#define PLAYER '@'
#define WALL '#'

class Screen
{
private:
    Player *player;
public:
    Screen(Player&);
    
    void Output();
};