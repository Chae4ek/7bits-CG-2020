#pragma once

#include <BearLibTerminal.h>

#include <map>
#include <memory>
#include <utility>
#include <vector>

#include "ECS/Components.h"
#include "ECS/Entity.h"

class MapManager {
 public:
  // Chunk (room) coords, entities in that chunk
  std::map<std::pair<int, int>, std::vector<std::unique_ptr<Entity>>> entities;

  int size_x = terminal_state(TK_WIDTH);
  int size_y = terminal_state(TK_HEIGHT) - 6;  // TODO: this looks like Screen system parameters (stats GUI)

  const Position *player;

  explicit MapManager(const Position *player) : player(player) {}

  void Add(Entity entity) {
    entities[GetChunkCoords()].emplace_back(std::make_unique<Entity>(std::move(entity)));
  }
  void Destroy(std::vector<std::unique_ptr<Entity>>::const_iterator entity) {
    entities.at(GetChunkCoords()).erase(entity);
  }
  inline bool CurrentIsEmpty() const {
    return !entities.count(GetChunkCoords());
  }
  constexpr std::pair<int, int> GetChunkCoords() const {
    int x = player->pos_x;
    int y = player->pos_y;
    if (x < 0) x -= size_x;
    if (y < 0) y -= size_y;
    return std::make_pair(x / size_x, y / size_y);
  }
};