#include "ControlSystem.h"

Controls::Controls(Player &player) : player(&player) {}

void Controls::Check(int key)
{
    if (key == KEY_LEFT) player->Left();
    if (key == KEY_RIGHT) player->Right();
    if (key == KEY_UP) player->Up();
    if (key == KEY_DOWN) player->Down();
}