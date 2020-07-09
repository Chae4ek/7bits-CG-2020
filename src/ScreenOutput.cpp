#include <BearLibTerminal.h>
#include "ScreenOutput.h"

Screen::Screen(Player &player) : player(&player) {}

void Screen::Output()
{
    terminal_put(player->GetPosX(), player->GetPosY(), PLAYER);
}