#include "Tools/MapManager.h"

MapManager::MapManager(const unsigned int seed, Position *player) : start_seed(seed), seed(seed), player(player) {}

void MapManager::CreateEntity(chunk_coords_t chunk_coords, Entity &&entity) {
  entities[chunk_coords].emplace_back(std::make_unique<Entity>(std::move(entity)));
}
void MapManager::Destroy(entity_ptr entity) {
  entities.at(entity.chunk_coords).erase(entity.iter);
}

bool MapManager::ChunkIsEmpty(const chunk_coords_t chunk_coords) const {
  return !entities.count(chunk_coords);
}
chunk_coords_t MapManager::GetChunkCoords(const Position *global_pos) const {
  int x = global_pos->pos_x;
  int y = global_pos->pos_y;
  if (x < 0) x -= size_x - 1;
  if (y < 0) y -= size_y - 1;
  return std::make_pair(x / size_x, y / size_y);
}

Position MapManager::GlobalToLocal(const Position global_pos) const {
  return GlobalToLocal(&global_pos);
}
Position MapManager::GlobalToLocal(const Position *global_pos) const {
  int xl = global_pos->pos_x % size_x;
  int yl = global_pos->pos_y % size_y;
  if (xl < 0) xl += size_x;
  if (yl < 0) yl += size_y;
  return Position(xl, yl);
}

entity_ptr MapManager::GetEntity(const chunk_coords_t chunk_coords, const Position local_pos) const {
  if (ChunkIsEmpty(chunk_coords)) return entity_ptr();

  entity_t entity = std::find_if(entities.at(chunk_coords).begin(), entities.at(chunk_coords).end(),
                                 [local_pos](const std::unique_ptr<Entity> &e) {
                                   Position *pos = e->Get<Position>();
                                   return local_pos.pos_x == pos->pos_x && local_pos.pos_y == pos->pos_y;
                                 });

  return entity_ptr(chunk_coords, entity, entity != entities.at(chunk_coords).end());
}

void MapManager::GoToLevel(const int level) {
  entities.clear();
  level_exit = true;
  level_id = level;

  if (level_last_pos.find(level) != level_last_pos.end()) {
    player->pos_x = level_last_pos.at(level)->pos_x;
    player->pos_y = level_last_pos.at(level)->pos_y;
  }

  seed = start_seed + level;
}