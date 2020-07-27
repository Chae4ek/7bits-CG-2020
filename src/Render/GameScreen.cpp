#include "Render/GameScreen.h"

GameScreen::GameScreen(const MapManager *map_manager, const Entity *player)
    : map_manager(map_manager), player_pos(player->Get<Position>()), player_sprite(player->Get<Sprite>()) {}

void GameScreen::Update() const {
  // TODO: delete and optimize this later
  terminal_clear();

  chunk_coords_t current_chunk = map_manager->GetChunkCoords(player_pos);
  if (map_manager->ChunkIsEmpty(current_chunk)) return;

  entity_t entity = map_manager->entities.at(current_chunk).begin();
  entity_t end = map_manager->entities.at(current_chunk).end();
  while (entity != end) {
    Print((*entity)->Get<Position>()->pos_x, (*entity)->Get<Position>()->pos_y, (*entity)->Get<Sprite>());
    ++entity;
  }

  Position player_local_pos = map_manager->GlobalToLocal(player_pos);
  Print(player_local_pos.pos_x, player_local_pos.pos_y, player_sprite);
}