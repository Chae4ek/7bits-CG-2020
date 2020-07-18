#include "ECS/Systems.h"

PlayerControl::PlayerControl(const Entity &player)
    : position(player.Get<Position>()), controls(player.Get<Controls>()), game_stats(player.Get<GameStats>()) {}

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

constexpr void PlayerControl::Left() {
  --position->pos_x;
  ++game_stats->step_count;
}
constexpr void PlayerControl::Right() {
  ++position->pos_x;
  ++game_stats->step_count;
}
constexpr void PlayerControl::Up() {
  --position->pos_y;
  ++game_stats->step_count;
}
constexpr void PlayerControl::Down() {
  ++position->pos_y;
  ++game_stats->step_count;
}