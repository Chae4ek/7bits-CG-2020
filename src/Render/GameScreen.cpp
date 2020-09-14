#include "Render/GameScreen.h"

GameScreen::GameScreen(const MapManager *map_manager, const Entity *player, const MenuProperties *menu_prop)
    : map_manager(map_manager),
      player_pos(player->Get<Position>()),
      player_sprite(player->Get<Sprite>()),
      menu_prop(menu_prop) {}

void GameScreen::Update() const {
  // TODO: delete and optimize this later
  terminal_clear();

  const chunk_coords_t current_chunk = map_manager->GetChunkCoords(player_pos);

  if (!map_manager->ChunkIsEmpty(current_chunk)) {
    entity_t entity = map_manager->entities.at(map_manager->GetLevel()).at(current_chunk).begin();
    const entity_t end = map_manager->entities.at(map_manager->GetLevel()).at(current_chunk).end();
    while (entity != end) {
      Print((*entity)->Get<Position>()->pos_x + pos_game_x, (*entity)->Get<Position>()->pos_y + pos_game_y,
            (*entity)->Get<Sprite>(), menu_prop->new_graphics);
      ++entity;
    }
  }

  const Position player_local_pos = map_manager->GlobalToLocal(player_pos);
  Print(player_local_pos.pos_x + pos_game_x, player_local_pos.pos_y + pos_game_y, player_sprite,
        menu_prop->new_graphics);
}