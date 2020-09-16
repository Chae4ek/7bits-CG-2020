#pragma once

#include "Constants.h"
#include "ECS/IComponent.h"

class Type : public IComponent {
 public:
  const ENTITY_TYPE type;

  explicit Type(const ENTITY_TYPE type) : type(type) {}
};