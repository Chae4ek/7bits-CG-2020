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

void Collision::AttackingEnemy(const Entity *mob) {
  Defense *player_def = player->Get<Defense>();
  const Defense *mob_def = mob->Get<Defense>();

  player_def->armor -= mob_def->armor;
  if (player_def->armor < 0) player_def->armor = 0;
  if (mob_def->health - player_def->armor > 0) player_def->health -= mob_def->health - player_def->armor;
  if (player_def->health <= 0) player_def->health = 0;  // TODO: death
}
int Collision::TryToAttack(Weapon *weapon) {
  const Position local_player_pos = map_manager->GlobalToLocal(player->Get<Position>());
  const entity_ptr entity =
      map_manager->GetEntity(map_manager->GetChunkCoords(player->Get<Position>()), local_player_pos);
  if (GetType(entity) == TYPE_ENEMY) {
    Defense *mob_def = entity.iter->get()->Get<Defense>();

    mob_def->armor -= weapon->armor_damage;
    if (mob_def->armor < 0) mob_def->armor = 0;
    if (weapon->health_damage - mob_def->armor > 0) mob_def->health -= weapon->health_damage - mob_def->armor;
    if (mob_def->health <= 0) map_manager->Destroy(entity);

    weapon->durability--;
    if (weapon->durability > 0) return 1;
    return 2;
  }
  return 0;
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