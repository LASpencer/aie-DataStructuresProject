#include "stdafx.h"
#include "Entity.h"
#include "Component.h"

Entity::Entity()
{
}


Entity::~Entity()
{
}

void Entity::addComponent(const ComponentPtr & component)
{
	//TODO figure out how to make this a lambda/function object
	int id = component->getID;
	bool alreadyPresent = false;
	for (auto& current : m_components) {
		if (current->getID() == id) {
			alreadyPresent = true;
			break;
		}
	}
	if (!alreadyPresent) {
		m_components.push_back(component);
	}
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
