#include "Tools/Collision.h"

Collision::Collision(MapManager *map_manager, Entity *player) : map_manager(map_manager), player(player) {}

ENTITY_TYPE Collision::GetType(const entity_ptr entity) const {
  if (!entity.valid) return TYPE_NULL;
  return (*entity.iter)->Get<Type>()->type;
}
void Collision::Collide(Entity *mob, entity_ptr entity) {
  const int type = GetType(entity);

  // TODO: replace to item dictionary
  switch (type) {
    case TYPE_WALL:
      break;
    case TYPE_COIN:
      mob->Get<GameStats>()->coins++;
      map_manager->Destroy(entity);
      break;
    case TYPE_EXIT:
      if (mob == player) map_manager->GoToLevel((*entity.iter)->Get<LevelExit>()->level);
      break;

    case TYPE_SWORD:
      if (mob == player) PickUpItem(entity);
      break;
    case TYPE_BOMB:
      if (mob == player) PickUpItem(entity);
      break;
    case TYPE_CHEST:
      if (mob == player) PickUpItem(entity);
      break;

    case TYPE_ENEMY:
      // if (mob == player) fighting
    default:
      break;
  }
}

void Collision::PickUpItem(entity_ptr entity) {
  Inventory *inv = player->Get<Inventory>();
  if (static_cast<int>(inv->inventory.size()) < inv->max_items) {
    auto &entities =
        map_manager->entities.at(map_manager->GetLevel()).at(map_manager->GetChunkCoords(player->Get<Position>()));

    inv->inventory.emplace_back(std::move(entities.at(entity.iter - entities.begin())));
    entities.erase(entity.iter);
  }
}