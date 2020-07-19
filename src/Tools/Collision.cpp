#include "Tools/Collision.h"

Collision::Collision(MapManager *map_manager, Entity *player) : map_manager(map_manager), player(player) {}

bool Collision::ForMovePlayer(entity_ptr entity) const {
  if (!entity.valid || (*entity.iter)->Get<Type>()->type != TYPE_WALL) return true;
  return false;
}

void Collision::CollidePlayer(entity_ptr entity) {
  if (!entity.valid) return;

  if ((*entity.iter)->Get<Type>()->type == TYPE_COIN) {
    player->Get<GameStats>()->coins++;
    map_manager->Destroy(entity);
  }
}