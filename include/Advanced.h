#pragma once

#include <map>

#include "ECS/Components/Sprite.h"

constexpr color_t COLOR_RED = 0xFFFF0000;
constexpr color_t COLOR_ORANGE = 0xFFFF7F00;
constexpr color_t COLOR_YELLOW = 0xFFFFFF00;
constexpr color_t COLOR_GREEN = 0xFF00FF00;
constexpr color_t COLOR_AQUA = 0xFF00FFFF;
constexpr color_t COLOR_BLUE = 0xFF3F42FF;
constexpr color_t COLOR_PURPLE = 0xFFBF00FF;
constexpr color_t COLOR_WHITE = 0xFFFFFFFF;
constexpr color_t COLOR_GREY = 0xFF7F7F7F;

enum ENTITY_TYPE {
  TYPE_NULL,
  TYPE_PLAYER,
  TYPE_COIN,
  TYPE_WALL,
  TYPE_EXIT,
  TYPE_SWORD,
  TYPE_BOMB,
  TYPE_CHEST,
  TYPE_ENEMY
};

const std::map<ENTITY_TYPE, Sprite> PREFABS = {
    {TYPE_NULL, Sprite('x', COLOR_RED, 0x1000)},    {TYPE_PLAYER, Sprite('@', COLOR_WHITE, 0x1001)},
    {TYPE_COIN, Sprite('$', COLOR_GREEN, 0x1002)},  {TYPE_WALL, Sprite('#', COLOR_GREY, 0x1003)},
    {TYPE_EXIT, Sprite('>', COLOR_AQUA, 0x1004)},   {TYPE_SWORD, Sprite('i', COLOR_PURPLE, 0x1005)},
    {TYPE_BOMB, Sprite('o', COLOR_ORANGE, 0x1006)}, {TYPE_CHEST, Sprite('X', COLOR_YELLOW, 0x1007)},
    {TYPE_ENEMY, Sprite('E', COLOR_RED, 0x1008)}};