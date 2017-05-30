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

	void addComponent(const ComponentPtr& component);

	virtual void update(float deltaTime);

	virtual void draw();

protected:
	las::Array<ComponentPtr> m_components;
};

