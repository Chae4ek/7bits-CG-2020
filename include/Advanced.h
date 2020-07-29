#pragma once

#include <BearLibTerminal.h>

#include <map>

#include "ECS/Components.h"

constexpr color_t COLOR_RED = 0xFFFF0000;
constexpr color_t COLOR_ORANGE = 0xFFFF7F00;
constexpr color_t COLOR_YELLOW = 0xFFFFFF00;
constexpr color_t COLOR_GREEN = 0xFF00FF00;
constexpr color_t COLOR_AQUA = 0xFF00FFFF;
constexpr color_t COLOR_BLUE = 0xFF3F42FF;
constexpr color_t COLOR_PURPLE = 0xFFBF00FF;
constexpr color_t COLOR_WHITE = 0xFFFFFFFF;
constexpr color_t COLOR_GREY = 0xFF7F7F7F;

constexpr int TYPE_NULL = 0;
constexpr int TYPE_PLAYER = 1;
constexpr int TYPE_COIN = 2;
constexpr int TYPE_WALL = 3;
constexpr int TYPE_EXIT = 4;

const std::map<int, Sprite> PREFABS = {{TYPE_NULL, Sprite('x', COLOR_RED)},
                                       {TYPE_PLAYER, Sprite('@', COLOR_WHITE)},
                                       {TYPE_COIN, Sprite('$', COLOR_YELLOW)},
                                       {TYPE_WALL, Sprite('#', COLOR_GREY)},
                                       {TYPE_EXIT, Sprite('>', COLOR_AQUA)}};