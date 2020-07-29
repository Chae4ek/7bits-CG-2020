#include "Tools/MapManager.h"

MapManager::MapManager(const unsigned int start_seed, Position *player)
    : start_seed(start_seed), player(player), seed(start_seed) {}

void MapManager::CreateEntity(const chunk_coords_t chunk_coords, Entity &&entity) {
  entities[level_id][chunk_coords].emplace_back(std::make_unique<Entity>(std::move(entity)));
}
void MapManager::Destroy(entity_ptr entity) {
  entities.at(level_id).at(entity.chunk_coords).erase(entity.iter);
}

void MapManager::SetLastPosition(const Position *player) {
  level_last_pos[level_id] = std::make_unique<Position>(player->pos_x, player->pos_y);
}
bool MapManager::LevelIsEmpty(const int level) const {
  return !level_last_pos.count(level);
}
int MapManager::GetLevel() const {
  return level_id;
}

bool MapManager::ChunkIsEmpty(const chunk_coords_t chunk_coords) const {
  return !entities.count(level_id) || !entities.at(level_id).count(chunk_coords);
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

  entity_t entity =
      std::find_if(entities.at(level_id).at(chunk_coords).begin(), entities.at(level_id).at(chunk_coords).end(),
                   [local_pos](const std::unique_ptr<Entity> &e) {
                     Position *pos = e->Get<Position>();
                     return local_pos.pos_x == pos->pos_x && local_pos.pos_y == pos->pos_y;
                   });

  return entity_ptr(chunk_coords, entity, entity != entities.at(level_id).at(chunk_coords).end());
}

void MapManager::GoToLevel(const int level) {
  level_exit = true;
  level_id = level;

  if (LevelIsEmpty(level)) {
    player->pos_x = 0;
    player->pos_y = 0;
  } else {
    player->pos_x = level_last_pos.at(level)->pos_x;
    player->pos_y = level_last_pos.at(level)->pos_y;
  }

  seed = start_seed + level;
}