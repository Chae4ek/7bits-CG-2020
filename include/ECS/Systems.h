#pragma once

#include <BearLibTerminal.h>
#include "Components.h"

// TODO: move to component of "Movement"
#define KEY_LEFT TK_LEFT
#define KEY_RIGHT TK_RIGHT
#define KEY_UP TK_UP
#define KEY_DOWN TK_DOWN

class PlayerControl
{
private:
	Position *player;
public:
	PlayerControl(Position *player);
	
	void Update(int key);
	
	int GetPosX();
	int GetPosY();
	
	void Left();
	void Right();
	void Up();
	void Down();
};

// TODO: move to component of "Sprite"
#define SPRITE_PLAYER '@'
#define SPRITE_WALL '#'

class Screen
{
private:
	Position *player;
public:
	Screen(Position *player);
	
	void Update();
};