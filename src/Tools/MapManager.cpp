#include "Tools/MapManager.h"

MapManager::MapManager(const unsigned int seed, const Position *player) : seed(seed), player(player) {
  Srand(seed);
}

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
  // TODO: replace to find function or find of coords
  auto entity = entities.at(chunk_coords).begin();
  auto end = entities.at(chunk_coords).end();
  Position *obj;

  while (entity != end) {
    obj = (*entity)->Get<Position>();

    if (local_pos.pos_x == obj->pos_x && local_pos.pos_y == obj->pos_y) break;

    ++entity;
  }

  return entity_ptr(chunk_coords, entity, end);
}