#pragma once

#include <BearLibTerminal.h>
#include "Components.h"
#include "Entity.h"

class PlayerControl
{
private:
	Position *player_pos;
	Movement *player_move;
	GameStats *player_stats;
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
	GameStats *player_stats;
	
	Sprite *wall_sprite;
public:
	Screen(Entity &player, Sprite &wall_sprite);
	
	void Update();
};