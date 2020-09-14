#include "Tools/Commands.h"

MoveEnemy::MoveEnemy(MapManager *map_manager, Entity *player, Entity *mob, Position new_pos)
    : map_manager(map_manager),
      player(player),
      mob(mob),
      new_pos(new_pos.pos_x, new_pos.pos_y),
      mob_pos(mob->Get<Position>()),
      mob_stats(mob->Get<GameStats>()),
      player_pos(player->Get<Position>()) {}

void MoveEnemy::Execute() {
  entity_ptr entity = map_manager->GetEntity(map_manager->GetChunkCoords(player_pos), new_pos);

  Collision collision(map_manager, player);

  if (collision.GetType(entity) != TYPE_WALL && collision.GetType(entity) != TYPE_ENEMY) {
    mob_pos->pos_x = new_pos.pos_x;
    mob_pos->pos_y = new_pos.pos_y;

    mob_stats->step_count++;

    Position local_player_pos = map_manager->GlobalToLocal(player_pos);
    if (local_player_pos.pos_x == mob_pos->pos_x && local_player_pos.pos_y == mob_pos->pos_y)
      collision.AttackingEnemy(mob);
  }
}