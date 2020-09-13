#include "Tools/Collision.h"

Collision::Collision(MapManager *map_manager, Entity *player) : map_manager(map_manager), player(player) {}

ENTITY_TYPE Collision::GetType(const entity_ptr entity) const {
  if (!entity.valid) return TYPE_NULL;
  return (*entity.iter)->Get<Type>()->type;
}
void Collision::CollidePlayer(entity_ptr entity) {
  const int type = GetType(entity);

  // TODO: replace to item dictionary
  switch (type) {
    case TYPE_WALL:
      break;
    case TYPE_COIN:
      player->Get<GameStats>()->coins++;
      map_manager->Destroy(entity);
      break;
    case TYPE_EXIT:
      map_manager->GoToLevel((*entity.iter)->Get<LevelExit>()->level);
      break;

    case TYPE_SWORD:
      PickUpItem(entity);
      break;
    case TYPE_BOMB:
      PickUpItem(entity);
      break;
    case TYPE_CHEST:
      PickUpItem(entity);
      break;
    default:
      break;
  }
}

void Collision::PickUpItem(entity_ptr entity) {
  if (static_cast<int>(player->Get<Inventory>()->inventory.size()) < player->Get<Inventory>()->max_items) {
    auto &entities =
        map_manager->entities.at(map_manager->GetLevel()).at(map_manager->GetChunkCoords(player->Get<Position>()));

    player->Get<Inventory>()->inventory.emplace_back(std::move(entities.at(entity.iter - entities.begin())));
    entities.erase(entity.iter);
  }
}