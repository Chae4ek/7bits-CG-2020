#include "ECS/Systems.h"

PlayerControl::PlayerControl(Position *player) : player(player) {}

void PlayerControl::Update(int key)
{
	if (key == KEY_LEFT) Left();
	if (key == KEY_RIGHT) Right();
	if (key == KEY_UP) Up();
	if (key == KEY_DOWN) Down();
}

int PlayerControl::GetPosX() { return player->pos_x; }
int PlayerControl::GetPosY() { return player->pos_y; }

void PlayerControl::Left() { --player->pos_x; }
void PlayerControl::Right() { ++player->pos_x; }
void PlayerControl::Up() { --player->pos_y; }
void PlayerControl::Down() { ++player->pos_y; }