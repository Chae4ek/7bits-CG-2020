#include "ECS/Systems/EnemyControl.h"

EnemyControl::EnemyControl(Entity *player, MapManager *map_manager)
    : player(player),
      map_manager(map_manager),
      player_pos(player->Get<Position>()),
      player_stats(player->Get<GameStats>()) {}

void EnemyControl::Update() {
  if (last_step_count == player_stats->step_count) return;
  last_step_count = player_stats->step_count;

  // following player
  const Position local_player_pos = map_manager->GlobalToLocal(player_pos);

  auto &entities = map_manager->entities.at(map_manager->GetLevel()).at(map_manager->GetChunkCoords(player_pos));
  std::vector<Entity *> enemies;
  std::for_each(entities.begin(), entities.end(), [&enemies](std::unique_ptr<Entity> &e) {
    if (e->Get<Type>()->type == TYPE_ENEMY) enemies.push_back(e.get());
  });

  for (Entity *mob : enemies) {
    Position *mob_pos = mob->Get<Position>();

    if (abs(mob_pos->pos_x - local_player_pos.pos_x) > abs(mob_pos->pos_y - local_player_pos.pos_y)) {
      if (local_player_pos.pos_x < mob_pos->pos_x && mob_pos->pos_x > 0)
        MoveEnemy(map_manager, player, mob, Position(mob_pos->pos_x - 1, mob_pos->pos_y)).Execute();
      else if (local_player_pos.pos_x > mob_pos->pos_x && mob_pos->pos_x < map_manager->size_x - 1)
        MoveEnemy(map_manager, player, mob, Position(mob_pos->pos_x + 1, mob_pos->pos_y)).Execute();
    } else {
      if (local_player_pos.pos_y < mob_pos->pos_y && mob_pos->pos_y > 0)
        MoveEnemy(map_manager, player, mob, Position(mob_pos->pos_x, mob_pos->pos_y - 1)).Execute();
      else if (local_player_pos.pos_y > mob_pos->pos_y && mob_pos->pos_y < map_manager->size_y - 1)
        MoveEnemy(map_manager, player, mob, Position(mob_pos->pos_x, mob_pos->pos_y + 1)).Execute();
    }
  }
}