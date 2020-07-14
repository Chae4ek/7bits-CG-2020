#pragma once

#include <BearLibTerminal.h>
#include "Components.h"
#include "MapManager.h"

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
	MapManager *map_manager;
	
	Position *player_pos;
	Sprite *player_sprite;
	GameStats *player_stats;
	
	Sprite *wall_sprite;
public:
	Screen(MapManager &map_manager, Entity &player, Sprite &wall_sprite);
	
	void Update();
	void PostUpdate();
};

class GenerateMap
{
private:
	unsigned int seed;
	MapManager *map_manager;
public:
	GenerateMap(unsigned int seed, MapManager &map_manager);
	
	void Update();
	
	void GenerateChunk();
};

class Collision
{
private:
	MapManager *map_manager;
	Entity *player;
	Position *player_pos;
public:
	Collision(MapManager &map_manager, Entity &player);
	
	void Update();
};