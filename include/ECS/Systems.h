#pragma once

#include <BearLibTerminal.h>
#include "Components.h"
#include "Entity.h"

class PlayerControl
{
private:
	Position *player_pos;
	Movement *player_move;
public:
	PlayerControl(Entity &player);
	
	void Update(int key);
	
	int GetPosX();
	int GetPosY();
	
	void Left();
	void Right();
	void Up();
	void Down();
};

class Screen
{
private:
	Position *player_pos;
	Sprite *player_sprite;
public:
	Screen(Entity &player);
	
	void Update();
};