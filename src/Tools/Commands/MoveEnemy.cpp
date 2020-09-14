#include "Tools/Commands.h"

MoveEnemy::MoveEnemy(MapManager *map_manager, Entity *player, Entity *mob, Position new_pos)
    : map_manager(map_manager),
      player(player),
      mob(mob),
      new_pos(new_pos.pos_x, new_pos.pos_y),
      mob_pos(mob ? mob->Get<Position>() : nullptr),
      mob_stats(mob ? mob->Get<GameStats>() : nullptr),
      player_pos(player->Get<Position>()) {}

void MoveEnemy::Execute() {
  entity_ptr entity = map_manager->GetEntity(map_manager->GetChunkCoords(player_pos), new_pos);

  Collision collision(map_manager, player);

  if (collision.GetType(entity) != TYPE_WALL && collision.GetType(entity) != TYPE_ENEMY) {
    mob_pos->pos_x = new_pos.pos_x;
    mob_pos->pos_y = new_pos.pos_y;

    mob_stats->step_count++;

    Position local_player_pos = map_manager->GlobalToLocal(player_pos);
    if (local_player_pos.pos_x == mob_pos->pos_x && local_player_pos.pos_y == mob_pos->pos_y) AttackingEnemy(mob);
  }
}

int MoveEnemy::AttackingEnemy(const Entity *mob) {
  Defense *player_def = player->Get<Defense>();
  const Defense *mob_def = mob->Get<Defense>();

  player_def->armor -= mob_def->armor;
  if (player_def->armor < 0) player_def->armor = 0;
  if (mob_def->health - player_def->armor > 0) player_def->health -= mob_def->health - player_def->armor;
  if (player_def->health <= 0) {
    PlayerDeath();
    return 1;
  }
  return 0;
}
int MoveEnemy::TryToAttack(Weapon *weapon) {
  const Position local_player_pos = map_manager->GlobalToLocal(player_pos);
  const entity_ptr entity = map_manager->GetEntity(map_manager->GetChunkCoords(player_pos), local_player_pos);
  if (entity.valid && entity.iter->get()->Get<Type>()->type == TYPE_ENEMY) {
    Defense *mob_def = entity.iter->get()->Get<Defense>();

    // TODO: make commands' pattern (for bomb, sword, etc.)
    mob_def->armor -= weapon->armor_damage;
    if (mob_def->armor < 0) mob_def->armor = 0;
    if (weapon->health_damage - mob_def->armor > 0) mob_def->health -= weapon->health_damage - mob_def->armor;
    if (mob_def->health <= 0)
      map_manager->Destroy(entity);
    else if (AttackingEnemy(entity.iter->get()))
      return 1;

    weapon->durability--;
    if (weapon->durability > 0) return 1;
    return 2;
  }
  return 0;
}

void MoveEnemy::PlayerDeath() {
  player->Get<Defense>()->health = map_manager->start_player_health;
  player->Get<Defense>()->armor = map_manager->start_player_armor;

  player->Get<GameStats>()->coins = 0;
  player->Get<GameStats>()->step_count = 0;

  Inventory *player_inv = player->Get<Inventory>();
  player_inv->cursor = 0;

  for (int i = 0; i < static_cast<int>(player_inv->inventory.size()); ++i) {
    player_inv->inventory.at(i)->Get<Position>()->pos_x = map_manager->GlobalToLocal(player_pos).pos_x;
    player_inv->inventory.at(i)->Get<Position>()->pos_y = map_manager->GlobalToLocal(player_pos).pos_y;

    map_manager->entities.at(map_manager->GetLevel())
        .at(map_manager->GetChunkCoords(player_pos))
        .emplace_back(std::move(player_inv->inventory.at(i)));
  }
  player_inv->inventory.clear();

  map_manager->SetLastPosAsFirstPos(map_manager->GetLevel());
  map_manager->SetLastPosAsFirstPos(-1);
  map_manager->GoToLevel(-1);
}