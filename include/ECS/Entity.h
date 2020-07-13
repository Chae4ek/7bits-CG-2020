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
	template<class Component_1, class... Components>
	void Add(Component_1 arg_1, Components ...args)
	{
		// TODO: remove recursion later?
		Add(arg_1);
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
		return dynamic_cast<Component*>(components[typeid(Component)].get());
	}
};