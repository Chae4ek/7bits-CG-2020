#pragma once

#include <vector>

#include "ECS/Components/ChestType.h"
#include "ECS/Components/Defense.h"
#include "ECS/Components/GameStats.h"
#include "ECS/Components/Inventory.h"
#include "ECS/Components/LevelExit.h"
#include "ECS/Components/Type.h"
#include "ECS/Components/Weapon.h"
#include "MapManager.h"
#include "ReaderStruct.h"

class Generate {
 private:
  MapManager *map_manager;
  Position *player;
  std::vector<struct_info> temp_structures;

  static unsigned int _SEED_RANDOM;

  const double smooth = 60;
  const double threshold = 0.125;
  const double sharp = 0.009;

  const double coin_chance = 4;
  const double chest_chance = 1;
  const double sword_chance = 0.5;
  const double bomb_chance = 0.5;
  const double enemy_chance = 10;
  const double structures_chance = 3;
  // TODO: delete this later
  const int structures_count = 1;
  const double exit_chance = 0.3;

 public:
  Generate(MapManager *map_manager, Position *player);

  void TryGenerateChunk(const chunk_coords_t chunk_coords);
  void CreateEntity(const ReaderStruct *reader, const ENTITY_TYPE type, const chunk_coords_t chunk_coords, const int x,
                    const int y);

  // empty = 0, single-block > 0, other < 0
  int GetStructureType(const chunk_coords_t chunk_global_pos, const int x, const int y) const;

  int L1(const chunk_coords_t chunk_global_pos, const int x, const int y) const;
  int L2(const chunk_coords_t chunk_global_pos, const int x, const int y) const;

  // range of [0, 1]
  double PerlinNoise(const double x, const double y) const;
  double DotGradient(int rand_x, int rand_y, double x, double y) const;
  constexpr double Lerp(const double a, const double b, double t) const;

  // range of [0, ...]
  static inline int Random();
  static inline void Srand(const unsigned int seed, const int seed1, const int seed2);
};