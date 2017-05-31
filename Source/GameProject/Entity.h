#pragma once
#include "stdafx.h"
#include "Array.h"

class Component;

typedef std::shared_ptr<Component> ComponentPtr;

class Entity
{
public:
	Entity();
	virtual ~Entity();

	bool addComponent(const ComponentPtr& component);

	bool removeComponent(int id);

	bool replaceComponent(const ComponentPtr& component);

	bool hasComponent(int id);

	ComponentPtr getComponent(int id);

	virtual void update(float deltaTime);

	virtual void draw();

protected:
	las::Array<ComponentPtr> m_components;
};

