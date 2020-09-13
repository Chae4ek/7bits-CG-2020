#pragma once

#include <memory>
#include <vector>

#include "ECS/Entity.h"

class Inventory : public IComponent {
 public:
  const int max_items;
  int cursor = 0;
  std::vector<std::unique_ptr<Entity>> inventory;

  explicit Inventory(const int max_items) : max_items(max_items) {}
};