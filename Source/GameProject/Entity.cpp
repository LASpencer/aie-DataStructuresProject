#include "stdafx.h"
#include "Entity.h"
#include "Component.h"

Entity::Entity() : m_position(std::make_shared<SceneObject>()), m_componentBitmask(0)
{
}


Entity::~Entity()
{
}

bool Entity::addComponent(const ComponentPtr & component)
{
	//TODO figure out how to make this a lambda/function object
	Component::Identifier id = component->getID();
	bool canAdd = true;
		if (m_componentBitmask & id) {
			canAdd = false;
		}
	if (canAdd) {
		canAdd = component->onAdd(this);
		if (canAdd) {
			m_components.push_back(component);
			m_componentBitmask |= id;
		}
	}
	return canAdd;
}

bool Entity::removeComponent(Component::Identifier id)
{
	las::Array<ComponentPtr>::iterator component = m_components.begin();
	bool removed = false;
	while (component != m_components.end()) {
		if ((*component)->getID() == id) {
			(*component)->onRemove(this);
			component = m_components.erase(component);
			m_componentBitmask &= !id;
			removed = true;
			break;
		} else {
			++component;
		}
	}
	return removed;
}


int Entity::getComponentMask()
{
	return m_componentBitmask;
}

ComponentPtr Entity::getComponent(Component::Identifier id)
{
	for (auto component : m_components) {
		if (component->getID() == id) {
			return component;
		}
	}
	return ComponentPtr();
}

SceneObjectPtr Entity::getPosition()
{
	return m_position;
}

void Entity::update(float deltaTime)
{
	for (auto& component : m_components) {
		component->update(this, deltaTime);
	}
}

void Entity::draw(aie::Renderer2D * renderer)
{
	for (auto& component : m_components) {
		component->draw(this, renderer);
	}
}
