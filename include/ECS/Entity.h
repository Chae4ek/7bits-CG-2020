#pragma once

#include <map>
#include <memory>
#include <typeindex>

#include "IComponent.h"

class Entity {
 private:
  std::map<std::type_index, std::unique_ptr<IComponent>> components;

 public:
  template<class... Components>
  explicit Entity(Components... args) {
    Add(args...);
  }
  template<class Component, class... Components>
  void Add(Component arg, Components... args) {
    // TODO: remove recursion later?
    Add(arg);
    Add(args...);
  }
  template<class Component>
  inline constexpr void Add(Component arg) {
    components[typeid(arg)] = std::make_unique<Component>(arg);
  }
  template<class Component>
  inline constexpr Component* Get() const {
    return dynamic_cast<Component*>(components.at(typeid(Component)).get());
  }
};