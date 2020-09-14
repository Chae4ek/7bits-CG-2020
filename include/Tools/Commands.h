#pragma once

#include "Collision.h"
#include "GenerateMap.h"
#include "ICommand.h"

class MovePlayer : public ICommand {
 private:
  MapManager *map_manager;
  Entity *player;
  Position new_pos;

  Position *player_pos;
  GameStats *player_stats;

 public:
  MovePlayer(MapManager *map_manager, Entity *player, Position new_pos);
  void Execute();
};

class MoveEnemy : public ICommand {
 private:
  MapManager *map_manager;
  Entity *player;
  Entity *mob;
  Position new_pos;

  Position *mob_pos;
  GameStats *mob_stats;
  Position *player_pos;

 public:
  MoveEnemy(MapManager *map_manager, Entity *player, Entity *mob, Position new_pos);
  void Execute();

  // 0 - just kick, 1 - player died
  int AttackingEnemy(const Entity *mob);
  void TryToAttack(Weapon *weapon);

  void PlayerDeath();
};