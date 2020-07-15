#include "ECS/Systems.h"

PlayerControl::PlayerControl(const Entity &player)
    : player_pos(player.Get<Position>()), player_move(player.Get<Movement>()), player_stats(player.Get<GameStats>()) {}

void PlayerControl::Update(int key) {
  if (key == player_move->KEY_LEFT) Left();
  if (key == player_move->KEY_RIGHT) Right();
  if (key == player_move->KEY_UP) Up();
  if (key == player_move->KEY_DOWN) Down();
}

constexpr int PlayerControl::GetPosX() {
  return player_pos->pos_x;
}
constexpr int PlayerControl::GetPosY() {
  return player_pos->pos_y;
}

constexpr void PlayerControl::Left() {
  --player_pos->pos_x;
  ++player_stats->step_count;
}
constexpr void PlayerControl::Right() {
  ++player_pos->pos_x;
  ++player_stats->step_count;
}
constexpr void PlayerControl::Up() {
  --player_pos->pos_y;
  ++player_stats->step_count;
}
constexpr void PlayerControl::Down() {
  ++player_pos->pos_y;
  ++player_stats->step_count;
}