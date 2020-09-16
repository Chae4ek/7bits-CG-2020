#pragma once

#include "Constants.h"
#include "ECS/IComponent.h"

class ChestType : public IComponent {
 public:
  const ENTITY_TYPE true_type;

  explicit ChestType(const ENTITY_TYPE true_type) : true_type(true_type) {}
};