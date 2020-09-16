#pragma once

#include "ECS/IComponent.h"

class Weapon : public IComponent {
 public:
  int durability;

  const int health_damage;
  const int armor_damage;

  Weapon(const int durability, const int health_damage, const int armor_damage)
      : durability(durability), health_damage(health_damage), armor_damage(armor_damage) {}
};