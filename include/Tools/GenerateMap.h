#pragma once

#include <vector>

#include "MapManager.h"
#include "ReaderStruct.h"

class Generate {
 public:
  MapManager *map_manager;
  std::vector<struct_info> temp_structures;

  static unsigned int _SEED_RANDOM;

  const double smooth = 60;
  const double threshold = 0.125;
  const double sharp = 0.009;

  const double coin_chance = 4;
  const double structures_chance = 3;
  // TODO: delete this later
  const int structures_count = 1;
  const double exit_chance = 0.3;

  explicit Generate(MapManager *map_manager);

  void TryGenerateChunk(const chunk_coords_t chunk_coords);
  void CreateEntity(const ReaderStruct *reader, const int type, chunk_coords_t chunk_coords, int x, int y);

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