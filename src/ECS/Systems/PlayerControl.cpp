#include "ECS/Systems/PlayerControl.h"

PlayerControl::PlayerControl(Entity *player, MapManager *map_manager)
    : player(player),
      map_manager(map_manager),
      position(player->Get<Position>()),
      controls(player->Get<Controls>()),
      game_stats(player->Get<GameStats>()) {}

void PlayerControl::Update(const int key) {
  if (map_manager->level_exit) return;

  if (key == controls->KEY_LEFT)
    MovePlayer(map_manager, player, Position(position->pos_x - 1, position->pos_y)).Execute();
  if (key == controls->KEY_RIGHT)
    MovePlayer(map_manager, player, Position(position->pos_x + 1, position->pos_y)).Execute();
  if (key == controls->KEY_UP)
    MovePlayer(map_manager, player, Position(position->pos_x, position->pos_y - 1)).Execute();
  if (key == controls->KEY_DOWN)
    MovePlayer(map_manager, player, Position(position->pos_x, position->pos_y + 1)).Execute();
}