#include "ECS/Systems/LevelExitControl.h"

LevelExitControl::LevelExitControl(Entity *player, MapManager *map_manager)
    : map_manager(map_manager), player_pos(player->Get<Position>()), controls(player->Get<Controls>()) {}

void LevelExitControl::Update(const int key) {
  if (map_manager->level_exit && key == controls->KEY_ENTER) {
    map_manager->level_exit = false;
    Generate(map_manager, player_pos).TryGenerateChunk(map_manager->GetChunkCoords(player_pos));
  }
}