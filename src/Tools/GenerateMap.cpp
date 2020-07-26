#include "Tools/GenerateMap.h"

Generate::Generate(MapManager* map_manager) : map_manager(map_manager) {}

void Generate::TryGenerateChunk(const chunk_coords_t chunk_coords, std::string level) {
  if (!map_manager->ChunkIsEmpty(chunk_coords)) return;

  const chunk_coords_t chunk_global_pos =
      std::make_pair(chunk_coords.first * map_manager->size_x, chunk_coords.second * map_manager->size_y);

  for (int x = 0; x < map_manager->size_x; ++x) {
    for (int y = 0; y < map_manager->size_y; ++y) {
      int structure_type = GetStructureType(chunk_global_pos, x + chunk_global_pos.first, y + chunk_global_pos.second);

      FILE* file = nullptr;
      ReaderStruct reader(x, y);
      bool generate = true;

      if (structure_type < 0 || level != "") {
        std::string struct_path = "./Structures/struct";
        if (level == "") {
          struct_path += std::to_string(structure_type);
        } else {
          struct_path += level;
          level = "";
        }
        file = fopen(struct_path.c_str(), "rb");
        generate = reader.SetStruct(file);
      }
      struct_info info = reader.GetInfo();

      if (info.x_bot < map_manager->size_x && info.y_bot < map_manager->size_y) {
        auto info_it = std::find_if(temp_structures.begin(), temp_structures.end(), [info](struct_info i) {
          // checking intersection of "info" and "i" structures
          return info.x_top <= i.x_bot && info.y_top <= i.y_bot && info.x_bot >= i.x_top && info.y_bot >= i.y_top;
        });
        if (info_it != temp_structures.end()) {
          y = info_it->y_bot;  // for speed up
          if (info_it->x_bot == x) temp_structures.erase(info_it);
        } else {
          // if none intersection
          if (generate) {
            if (info.x_top == info.x_bot && info.y_top == info.y_bot) {
              CreateEntity(structure_type, chunk_coords, info.x_top, info.y_top);
            } else {
              if (info.x_top != info.x_bot) temp_structures.push_back(info);  // if(...) for speed up
              for (int i = info.x_top; i <= info.x_bot; ++i)
                for (int j = info.y_top; j <= info.y_bot; ++j)
                  CreateEntity(reader.GetNextEntityType(), chunk_coords, i, j);
            }
          }
        }
      }

      if (file) fclose(file);
    }
  }
}
void Generate::CreateEntity(const int type, chunk_coords_t chunk_coords, int x, int y) {
  if (type == TYPE_PLAYER) {
    map_manager->player->pos_x = x;
    map_manager->player->pos_y = y;
  } else {
    if (type != TYPE_NULL)
      map_manager->CreateEntity(chunk_coords,
                                Entity(Type(type), map_manager->GlobalToLocal(Position(x, y)), PREFABS.at(type)));
  }
}

int Generate::GetStructureType(const chunk_coords_t chunk_global_pos, const int x, const int y) const {
  if (!x && !y) return TYPE_NULL;

  double noise = PerlinNoise(x / smooth, y / smooth);
  Srand(map_manager->seed, x * map_manager->size_x, y * map_manager->size_y);

  if ((noise > threshold + sharp || Random() % 2) && ((noise > threshold - sharp && Random() % 2) || noise > threshold))
    return TYPE_WALL;

  Srand(map_manager->seed, Random() + chunk_global_pos.first, Random() + chunk_global_pos.second);

  if (Random() % static_cast<int>(map_manager->size_x * map_manager->size_y / coin_chance) == 0) return TYPE_COIN;

  // TODO: replace to dictionary?
  if (Random() % static_cast<int>(map_manager->size_x * map_manager->size_y / structures_chance) == 0)
    return -Random() % structures_count - 1;
  if (Random() % static_cast<int>(map_manager->size_x * map_manager->size_y / exit_chance) == 0) return -2;

  return TYPE_NULL;
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
  Srand(map_manager->seed, rand_x, rand_y);

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