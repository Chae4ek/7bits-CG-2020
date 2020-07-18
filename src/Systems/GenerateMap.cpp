#include "Advanced.h"
#include "ECS/Systems.h"

GenerateMap::GenerateMap(const unsigned int seed, MapManager *map_manager) : seed(seed), map_manager(map_manager) {
  Srand(seed);
}

void GenerateMap::Update() {
  // TODO: move it to player class for optimization?
  // when player outside screen, this must be check
  if (map_manager->CurrentIsEmpty()) GenerateChunk();
}
void GenerateMap::GenerateChunk() {
  int count_coins = Random() % 15 + 5;
  while (count_coins--) {
    // TODO: coords should NOT be equal!
    map_manager->CreateEntity(Type(TYPE_COIN), Position(Random() % map_manager->size_x, Random() % map_manager->size_y),
                              Sprite('$', COLOR_YELLOW));
  }
}