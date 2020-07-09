#include "Control.h"

Control::Control(Player &player) : player(&player) {}

void Control::Check(int key)
{
    if (key == KEY_LEFT) player->Left();
    if (key == KEY_RIGHT) player->Right();
    if (key == KEY_UP) player->Up();
    if (key == KEY_DOWN) player->Down();
}