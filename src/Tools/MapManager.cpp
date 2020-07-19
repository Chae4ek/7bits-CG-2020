#include "Tools/MapManager.h"

MapManager::MapManager(const unsigned int seed, const Position *player) : seed(seed), player(player) {
  Srand(seed);
}

template<class... Components>
void MapManager::CreateEntity(chunk_coords_t chunk_coords, Components... args) {
  entities[chunk_coords].emplace_back(std::make_unique<Entity>(args...));
}
void MapManager::Destroy(entity_ptr entity) {
  entities.at(entity.chunk_coords).erase(entity.iter);
}
inline bool MapManager::ChunkIsEmpty(const chunk_coords_t chunk_coords) const {
  return !entities.count(chunk_coords);
}
chunk_coords_t MapManager::GetChunkCoords(const Position *global_pos) const {
  int x = global_pos->pos_x;
  int y = global_pos->pos_y;
  if (x < 0) x -= size_x;
  if (y < 0) y -= size_y;
  return std::make_pair(x / size_x, y / size_y);
}

Position MapManager::GlobalToLocal(const Position *global_pos) const {
  int xl = global_pos->pos_x % size_x;
  int yl = global_pos->pos_y % size_y;
  if (xl < 0) xl += size_x;
  if (yl < 0) yl += size_y;
  return Position(xl, yl);
}

void MapManager::TryGenerateChunk(const chunk_coords_t chunk_coords) {
  if (!ChunkIsEmpty(chunk_coords)) return;

  int count_coins = Random() % 15 + 5;
  while (count_coins--) {
    // TODO: coords should NOT be equal!
    CreateEntity(chunk_coords, Type(TYPE_COIN), Position(Random() % size_x, Random() % size_y),
                 Sprite(TEXTURE_COIN, COLOR_YELLOW));
  }
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