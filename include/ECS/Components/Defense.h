#pragma once

#include "ECS/IComponent.h"

class Defense : public IComponent {
 public:
  int health;
  int armor;

  Defense(const int health, const int armor) : health(health), armor(armor) {}
};