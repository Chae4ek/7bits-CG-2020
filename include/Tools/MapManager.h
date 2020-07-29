#pragma once

#include <BearLibTerminal.h>

#include <algorithm>
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

  entity_ptr() : valid(false) {}
  entity_ptr(const chunk_coords_t chunk_coords, const entity_t entity, const bool valid)
      : chunk_coords(chunk_coords), iter(entity), valid(valid) {}
};

class MapManager {
 private:
  std::map<int, std::unique_ptr<Position>> level_last_pos;
  int level_id = -1;

  const unsigned int start_seed;

  Position *player;

 public:
  // TODO: private this later
  std::map<int, std::map<chunk_coords_t, std::vector<std::unique_ptr<Entity>>>> entities;
  bool level_exit = false;

  const int size_x = terminal_state(TK_WIDTH);
  const int size_y = terminal_state(TK_HEIGHT) - 6;  // TODO: this looks like GUIScreen system parameters

  unsigned int seed;

  MapManager(const unsigned int start_seed, Position *player);

  void CreateEntity(const chunk_coords_t chunk_coords, Entity &&entity);
  void Destroy(entity_ptr entity);

  void SetLastPosition(const Position *player);
  bool LevelIsEmpty(const int level) const;
  int GetLevel() const;

  bool ChunkIsEmpty(const chunk_coords_t chunk_coords) const;
  chunk_coords_t GetChunkCoords(const Position *global_pos) const;

  Position GlobalToLocal(const Position global_pos) const;
  Position GlobalToLocal(const Position *global_pos) const;

  entity_ptr GetEntity(const chunk_coords_t chunk_coords, const Position local_pos) const;

  void GoToLevel(const int level);
};