#include "Player.h"

Player::Player()
{
    pos_x = 0;
    pos_y = 0;
}

int Player::GetPosX() { return pos_x; }
int Player::GetPosY() { return pos_y; }

void Player::Left() { --pos_x; }
void Player::Right() { ++pos_x; }
void Player::Up() { --pos_y; }
void Player::Down() { ++pos_y; }