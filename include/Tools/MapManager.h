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
typedef std::vector<std::unique_ptr<Entity>>::const_iterator entity_t;

struct entity_ptr {
 public:
  const chunk_coords_t chunk_coords;
  const entity_t iter;
  const bool valid;

  entity_ptr(chunk_coords_t chunk_coords, entity_t entity, entity_t end)
      : chunk_coords(chunk_coords), iter(entity), valid(entity != end) {}
};

class MapManager {
 public:
  std::map<chunk_coords_t, std::vector<std::unique_ptr<Entity>>> entities;
  // TODO: create structures container?

  int size_x = terminal_state(TK_WIDTH);
  int size_y = terminal_state(TK_HEIGHT) - 6;  // TODO: this looks like Screen system parameters (stats GUI)

  const unsigned int seed;

  const Position *player;

  MapManager(const unsigned int seed, const Position *player);

  void CreateEntity(chunk_coords_t chunk_coords, Entity &&entity);
  void Destroy(entity_ptr entity);

  bool ChunkIsEmpty(const chunk_coords_t chunk_coords) const;
  chunk_coords_t GetChunkCoords(const Position *global_pos) const;

  Position GlobalToLocal(const Position global_pos) const;
  Position GlobalToLocal(const Position *global_pos) const;

  entity_ptr GetEntity(const chunk_coords_t chunk_coords, const Position local_pos) const;
};