#include "Tools/GenerateMap.h"

Generate::Generate(MapManager *map_manager) : map_manager(map_manager), seed(map_manager->seed) {}

void Generate::TryGenerateChunk(const chunk_coords_t chunk_coords) {
  if (!map_manager->ChunkIsEmpty(chunk_coords)) return;

  const chunk_coords_t chunk_global_pos =
      std::make_pair(chunk_coords.first * map_manager->size_x, chunk_coords.second * map_manager->size_y);

  for (int x = 0; x < map_manager->size_x; ++x) {
    for (int y = 0; y < map_manager->size_y; ++y) {
      // TODO: if current is not structure then "continue;" (for non-single-block structures)
      Entity structure = GetStructure(chunk_global_pos, x + chunk_global_pos.first, y + chunk_global_pos.second);
      if (structure.Get<Type>()->type != TYPE_NULL) map_manager->CreateEntity(chunk_coords, std::move(structure));
    }
  }
}

// TODO: make structures
Entity Generate::GetStructure(const chunk_coords_t chunk_global_pos, const int x, const int y) const {
  double noise = PerlinNoise(x / smooth, y / smooth);
  Srand(seed, x * map_manager->size_x, y * map_manager->size_y);

  if ((noise > threshold + sharp || Random() % 2) && ((noise > threshold - sharp && Random() % 2) || noise > threshold))
    return Entity(Type(TYPE_WALL), map_manager->GlobalToLocal(Position(x, y)), Sprite(TEXTURE_WALL, COLOR_GREY));

  Srand(seed, Random() + chunk_global_pos.first, Random() + chunk_global_pos.second);

  if (Random() % (map_manager->size_x * map_manager->size_y / coin_chance) == 0)
    return Entity(Type(TYPE_COIN), map_manager->GlobalToLocal(Position(x, y)), Sprite(TEXTURE_COIN, COLOR_YELLOW));

  return Entity(Type(TYPE_NULL));
}
double Generate::PerlinNoise(const double x, const double y) const {
  int x0 = static_cast<int>(x);
  int y0 = static_cast<int>(y);
  int x1 = x0 + 1;
  int y1 = y0 + 1;

  double tx = x - x0;
  double d1, d2, lerp_x_top, lerp_x_bottom;

  d1 = DotGradient(x0, y0, x, y);
  d2 = DotGradient(x1, y0, x, y);
  lerp_x_top = Lerp(d1, d2, tx);

  d1 = DotGradient(x0, y1, x, y);
  d2 = DotGradient(x1, y1, x, y);
  lerp_x_bottom = Lerp(d1, d2, tx);

  double lerp_xy = Lerp(lerp_x_top, lerp_x_bottom, y - y0);
  if (lerp_xy < 0) lerp_xy *= -1;
  return lerp_xy;
}
double Generate::DotGradient(int rand_x, int rand_y, double x, double y) const {
  Srand(seed, rand_x, rand_y);

  int r = Random() % 4;
  x -= rand_x;
  y -= rand_y;

  if (r == 0)
    rand_x = 0, rand_y = 1;
  else if (r == 1)
    rand_x = 0, rand_y = -1;
  else if (r == 2)
    rand_x = 1, rand_y = 0;
  else
    rand_x = -1, rand_y = 0;

  return x * rand_x + y * rand_y;
}
constexpr double Generate::Lerp(const double a, const double b, double t) const {
  t = t * t * t * (t * (t * 6 - 15) + 10);
  return a + (b - a) * t;
}