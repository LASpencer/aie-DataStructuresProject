#pragma once
#include "stdafx.h"
#include "Array.h"
#include "Renderer2D.h"
#include "Component.h"

typedef std::shared_ptr<Component> ComponentPtr;

class Entity
{
public:
	Entity();
	virtual ~Entity();

	bool addComponent(const ComponentPtr& component);

	bool removeComponent(Component::Identifier id);

	bool replaceComponent(const ComponentPtr& component);

	bool hasComponent(Component::Identifier id);

	ComponentPtr getComponent(Component::Identifier id);

	virtual void update(float deltaTime);

	virtual void draw(aie::Renderer2D* renderer);

protected:
	las::Array<ComponentPtr> m_components; //HACK: A map might be better?
};

