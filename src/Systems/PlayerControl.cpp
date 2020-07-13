#include "ECS/Systems.h"

PlayerControl::PlayerControl(Entity &player) :
	player_pos(player.Get<Position>()),
	player_move(player.Get<Movement>()) {}

void PlayerControl::Update(int key)
{
	if (key == player_move->KEY_LEFT) Left();
	if (key == player_move->KEY_RIGHT) Right();
	if (key == player_move->KEY_UP) Up();
	if (key == player_move->KEY_DOWN) Down();
}

int PlayerControl::GetPosX() { return player_pos->pos_x; }
int PlayerControl::GetPosY() { return player_pos->pos_y; }

void PlayerControl::Left() { --player_pos->pos_x; }
void PlayerControl::Right() { ++player_pos->pos_x; }
void PlayerControl::Up() { --player_pos->pos_y; }
void PlayerControl::Down() { ++player_pos->pos_y; }