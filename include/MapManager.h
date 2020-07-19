#pragma once

#include <BearLibTerminal.h>

#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "Advanced.h"
#include "ECS/Components.h"
#include "ECS/Entity.h"

typedef std::pair<int, int> chunk_coords_t;

class MapManager {
 public:
  std::map<chunk_coords_t, std::vector<std::unique_ptr<Entity>>> entities;

  int size_x = terminal_state(TK_WIDTH);
  int size_y = terminal_state(TK_HEIGHT) - 6;  // TODO: this looks like Screen system parameters (stats GUI)

  const unsigned int seed;

  const Position *player;

  MapManager(const unsigned int seed, const Position *player) : seed(seed), player(player) {
    Srand(seed);
  }

  template<class... Components>
  void CreateEntity(chunk_coords_t chunk_coords, Components... args) {
    entities[chunk_coords].emplace_back(std::make_unique<Entity>(args...));
  }
  void Destroy(chunk_coords_t chunk_coords, std::vector<std::unique_ptr<Entity>>::const_iterator entity) {
    entities.at(chunk_coords).erase(entity);
  }

  inline bool ChunkIsEmpty(const chunk_coords_t chunk_coords) const {
    return !entities.count(chunk_coords);
  }
  constexpr chunk_coords_t GetChunkCoords(const Position *global_pos) const {
    int x = global_pos->pos_x;
    int y = global_pos->pos_y;
    if (x < 0) x -= size_x;
    if (y < 0) y -= size_y;
    return std::make_pair(x / size_x, y / size_y);
  }

  Position GlobalToLocal(const Position *global_pos) const {
    int xl = global_pos->pos_x % size_x;
    int yl = global_pos->pos_y % size_y;
    if (xl < 0) xl += size_x;
    if (yl < 0) yl += size_y;
    return Position(xl, yl);
  }

  void TryGenerateChunk(const chunk_coords_t chunk_coords) {
    if (!ChunkIsEmpty(chunk_coords)) return;

    int count_coins = Random() % 15 + 5;
    while (count_coins--) {
      // TODO: coords should NOT be equal!
      CreateEntity(chunk_coords, Type(TYPE_COIN), Position(Random() % size_x, Random() % size_y),
                   Sprite(TEXTURE_COIN, COLOR_YELLOW));
    }
  }

  std::pair<std::vector<std::unique_ptr<Entity>>::const_iterator, std::vector<std::unique_ptr<Entity>>::const_iterator>
  GetCollide(const chunk_coords_t chunk_coords, const Position local_pos) const {
    // TODO: replace to find function or find of coords
    auto entity = entities.at(chunk_coords).begin();
    auto end = entities.at(chunk_coords).end();
    Position *obj;

    while (entity != end) {
      obj = (*entity)->Get<Position>();

      if (local_pos.pos_x == obj->pos_x && local_pos.pos_y == obj->pos_y) break;

      ++entity;
    }

    return std::make_pair(entity, end);
  }
};