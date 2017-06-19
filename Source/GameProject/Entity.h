#pragma once
#include "stdafx.h"
#include "Array.h"
#include "Renderer2D.h"
#include "Component.h"
#include "SceneObject.h"

typedef std::shared_ptr<Component> ComponentPtr;

class Entity
{
public:
	Entity();
	virtual ~Entity();

	bool addComponent(const ComponentPtr& component);

	bool removeComponent(Component::Identifier id);

	int getComponentMask();

	ComponentPtr getComponent(Component::Identifier id);

	SceneObjectPtr getPosition();

	virtual void update(float deltaTime);

	virtual void draw(aie::Renderer2D* renderer);

protected:
	las::Array<ComponentPtr> m_components; //HACK: A map might be better?
	int m_componentBitmask;
	SceneObjectPtr m_position;
};

