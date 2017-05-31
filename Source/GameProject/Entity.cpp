#include "stdafx.h"
#include "Entity.h"
#include "Component.h"

Entity::Entity()
{
}


Entity::~Entity()
{
}

bool Entity::addComponent(const ComponentPtr & component)
{
	//TODO figure out how to make this a lambda/function object
	int id = component->getID();
	bool canAdd = true;
	for (auto& current : m_components) {
		if (current->getID() == id) {
			canAdd = false;
			break;
		}
	}
	if (canAdd) {
		canAdd = component->onAdd(this);
		if (canAdd) {
			m_components.push_back(component);
		}
	}
	return canAdd;
}

bool Entity::removeComponent(int id)
{
	las::Array<ComponentPtr>::iterator component = m_components.begin();
	bool removed = false;
	while (component != m_components.end()) {
		if ((*component)->getID() == id) {
			component = m_components.erase(component);
			removed = true;
			break;
		} else {
			++component;
		}
	}
	return removed;
}

bool Entity::replaceComponent(const ComponentPtr & component)
{
	int id = component->getID();
	bool replaced = false;
	bool added = false;
	for (auto& current : m_components) {
		if (current->getID() == id) {
			current = component;
			replaced = true;
			break;
		}
	}
	if (!replaced) {
		m_components.push_back(component);
		bool added = true;
	}
	return replaced || added;
}

bool Entity::hasComponent(int id)
{
	for (auto& component : m_components) {
		if (component->getID() == id) {
			return true;
		}
	}
	return false;
}

ComponentPtr Entity::getComponent(int id)
{
	for (auto component : m_components) {
		if (component->getID() == id) {
			return component;
		}
	}
	return ComponentPtr();
}

void Entity::update(float deltaTime)
{
	for (auto& component : m_components) {
		component->update(this, deltaTime);
	}
}

void Entity::draw()
{
	for (auto& component : m_components) {
		component->draw(this);
	}
}
