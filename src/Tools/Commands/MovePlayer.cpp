#include "Tools/Commands.h"

MovePlayer::MovePlayer(MapManager *map_manager, Entity *player, Position new_pos)
    : map_manager(map_manager), player(player), new_pos(new_pos.pos_x, new_pos.pos_y) {}

void MovePlayer::Execute() {
  chunk_coords_t chunk_coords = map_manager->GetChunkCoords(&new_pos);
  map_manager->TryGenerateChunk(chunk_coords);

  entity_ptr entity = map_manager->GetEntity(chunk_coords, map_manager->GlobalToLocal(&new_pos));

  Collision collision(map_manager, player);

  if (collision.ForMovePlayer(entity)) {
    player->Get<Position>()->pos_x = new_pos.pos_x;
    player->Get<Position>()->pos_y = new_pos.pos_y;

    player->Get<GameStats>()->step_count++;

    collision.CollidePlayer(entity);
  }
}