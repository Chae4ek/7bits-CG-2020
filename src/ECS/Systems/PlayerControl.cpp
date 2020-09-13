#include "ECS/Systems/PlayerControl.h"

PlayerControl::PlayerControl(Entity *player, MapManager *map_manager)
    : player(player),
      map_manager(map_manager),
      player_pos(player->Get<Position>()),
      controls(player->Get<Controls>()),
      player_stats(player->Get<GameStats>()),
      player_inv(player->Get<Inventory>()) {}

void PlayerControl::Update(const int key) {
  if (map_manager->level_exit) return;

  // TODO: replace to alternative keys
  if (key == controls->KEY_LEFT)
    MovePlayer(map_manager, player, Position(player_pos->pos_x - 1, player_pos->pos_y)).Execute();
  if (key == controls->KEY_RIGHT)
    MovePlayer(map_manager, player, Position(player_pos->pos_x + 1, player_pos->pos_y)).Execute();
  if (key == controls->KEY_UP)
    MovePlayer(map_manager, player, Position(player_pos->pos_x, player_pos->pos_y - 1)).Execute();
  if (key == controls->KEY_DOWN)
    MovePlayer(map_manager, player, Position(player_pos->pos_x, player_pos->pos_y + 1)).Execute();

  // TODO: replace to ARROWS ?
  if (key == controls->KEY_1 && 1 <= player_inv->max_items) player_inv->cursor = 0;
  if (key == controls->KEY_2 && 2 <= player_inv->max_items) player_inv->cursor = 1;
  if (key == controls->KEY_3 && 3 <= player_inv->max_items) player_inv->cursor = 2;
  if (key == controls->KEY_4 && 4 <= player_inv->max_items) player_inv->cursor = 3;
  if (key == controls->KEY_5 && 5 <= player_inv->max_items) player_inv->cursor = 4;
  if (key == controls->KEY_6 && 6 <= player_inv->max_items) player_inv->cursor = 5;
  if (key == controls->KEY_7 && 7 <= player_inv->max_items) player_inv->cursor = 6;
  if (key == controls->KEY_8 && 8 <= player_inv->max_items) player_inv->cursor = 7;

  // TODO: make commands' pattern
  if (key == controls->KEY_ENTER && player_inv->cursor < static_cast<int>(player_inv->inventory.size())) {
    player_inv->inventory.at(player_inv->cursor).get()->Get<Position>()->pos_x =
        map_manager->GlobalToLocal(player_pos).pos_x;
    player_inv->inventory.at(player_inv->cursor).get()->Get<Position>()->pos_y =
        map_manager->GlobalToLocal(player_pos).pos_y;

    map_manager->entities.at(map_manager->GetLevel())
        .at(map_manager->GetChunkCoords(player->Get<Position>()))
        .emplace_back(std::move(player_inv->inventory.at(player_inv->cursor)));

    player_inv->inventory.erase(player_inv->inventory.begin() + player_inv->cursor);
  }
}