#include "Advanced.h"
#include "ECS/Systems.h"

Collision::Collision(MapManager *map_manager, const Entity &player)
    : map_manager(map_manager), player(&player), player_pos(player.Get<Position>()) {}

void Collision::Update() {
  auto player_local_pos = GlobalToLocal(map_manager, player_pos->pos_x, player_pos->pos_y);

  auto entity = map_manager->entities[map_manager->GetChunkCoords()].begin();
  auto end = map_manager->entities[map_manager->GetChunkCoords()].end();
  while (entity != end) {
    Position *obj = (*entity)->Get<Position>();
    if (player_local_pos.first == obj->pos_x && player_local_pos.second == obj->pos_y) {
      if ((*entity)->Get<Type>()->type == TYPE_COIN) {
        player->Get<GameStats>()->coins++;
        map_manager->Destroy(entity);
        break;
      }
    }

    ++entity;
  }
}