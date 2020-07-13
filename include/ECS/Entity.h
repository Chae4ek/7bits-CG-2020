#pragma once

#include <map>
#include <memory>
#include <typeindex>
#include "Component.h"

class Entity
{
private:
	std::map<std::type_index, std::unique_ptr<IComponent>> components;
public:
	template<class... Components>
	Entity(Components ...args)
	{
		Add(args...);
	}
	template<class Component, class... Components>
	void Add(Component arg, Components ...args)
	{
		// TODO: remove recursion later?
		Add(arg);
		Add(args...);
	}
	template<class Component>
	void Add(Component arg)
	{
		components[typeid(arg)] = std::make_unique<Component>(arg);
	}
	template<class Component>
	Component* Get()
	{
		return dynamic_cast<Component*>(components.at(typeid(Component)).get());
	}
};