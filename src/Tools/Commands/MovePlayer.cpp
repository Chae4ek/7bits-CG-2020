#include "Tools/Commands.h"

MovePlayer::MovePlayer(MapManager *map_manager, Entity *player, Position new_pos)
    : map_manager(map_manager),
      player(player),
      new_pos(new_pos.pos_x, new_pos.pos_y),
      player_pos(player->Get<Position>()),
      player_stats(player->Get<GameStats>()),
      player_inv(player->Get<Inventory>()) {}

void MovePlayer::Execute() {
  const chunk_coords_t chunk_coords = map_manager->GetChunkCoords(&new_pos);

  Generate(map_manager, player_pos).TryGenerateChunk(chunk_coords);

  entity_ptr entity = map_manager->GetEntity(chunk_coords, map_manager->GlobalToLocal(&new_pos));

  Collision collision(map_manager, player);

  if (collision.GetType(entity) != TYPE_WALL) {
    map_manager->SavePlayerPosition();

    player_pos->pos_x = new_pos.pos_x;
    player_pos->pos_y = new_pos.pos_y;

    player_stats->step_count++;

    collision.CollidePlayer(entity);
  }
}