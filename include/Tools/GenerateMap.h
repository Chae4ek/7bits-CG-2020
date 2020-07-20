#pragma once

#include "MapManager.h"

class Generate {
 public:
  MapManager *map_manager;

  const unsigned int seed;

  const double smooth = 60;
  const double threshold = 0.125;
  const double sharp = 0.009;

  const int coin_chance = 4;

  explicit Generate(MapManager *map_manager);

  void TryGenerateChunk(const chunk_coords_t chunk_coords);

  Entity GetStructure(const chunk_coords_t chunk_global_pos, const int x, const int y) const;
  // Range of [0, 1]
  double PerlinNoise(const double x, const double y) const;
  double DotGradient(int rand_x, int rand_y, double x, double y) const;
  constexpr double Lerp(const double a, const double b, double t) const;
};