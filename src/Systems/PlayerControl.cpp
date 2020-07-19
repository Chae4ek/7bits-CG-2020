#include "ECS/Systems.h"

PlayerControl::PlayerControl(const Entity *player, MapManager *map_manager)
    : map_manager(map_manager),
      position(player->Get<Position>()),
      controls(player->Get<Controls>()),
      game_stats(player->Get<GameStats>()) {}

void PlayerControl::Update(int key) {
  if (key == controls->KEY_LEFT) Left();
  if (key == controls->KEY_RIGHT) Right();
  if (key == controls->KEY_UP) Up();
  if (key == controls->KEY_DOWN) Down();
}

constexpr int PlayerControl::GetPosX() {
  return position->pos_x;
}
constexpr int PlayerControl::GetPosY() {
  return position->pos_y;
}

inline void PlayerControl::Left() {
  Position new_pos(position->pos_x - 1, position->pos_y);
  TryGoToPos(&new_pos);
}
inline void PlayerControl::Right() {
  Position new_pos(position->pos_x + 1, position->pos_y);
  TryGoToPos(&new_pos);
}
inline void PlayerControl::Up() {
  Position new_pos(position->pos_x, position->pos_y - 1);
  TryGoToPos(&new_pos);
}
inline void PlayerControl::Down() {
  Position new_pos(position->pos_x, position->pos_y + 1);
  TryGoToPos(&new_pos);
}

// TODO: replace to command pattern
inline void PlayerControl::TryGoToPos(const Position *new_pos) {
  auto chunk_coords = map_manager->GetChunkCoords(new_pos);
  map_manager->TryGenerateChunk(chunk_coords);

  auto entity = map_manager->GetCollide(chunk_coords, map_manager->GlobalToLocal(new_pos));
  if (entity.first == entity.second || (*entity.first)->Get<Type>()->type != TYPE_WALL) {
    position->pos_x = new_pos->pos_x;
    position->pos_y = new_pos->pos_y;

    ++game_stats->step_count;

    if (entity.first != entity.second && (*entity.first)->Get<Type>()->type == TYPE_COIN) {
      ++game_stats->coins;
      map_manager->Destroy(chunk_coords, entity.first);
    }
  }
}