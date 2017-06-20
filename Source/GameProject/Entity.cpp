#include "stdafx.h"
#include "Entity.h"
#include "Component.h"

Entity::Entity() : m_position(std::make_shared<SceneObject>()), m_componentMask(0)
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
		if (m_componentMask & id) {
			canAdd = false;
		}
	if (canAdd) {
		canAdd = component->onAdd(shared_from_this());
		if (canAdd) {
			m_components.push_back(component);
			m_componentMask |= id;
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
			(*component)->onRemove(shared_from_this());
			component = m_components.erase(component);
			m_componentMask &= !id;
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
	return m_componentMask;
}

void Entity::addTag(ETag tag)
{
	m_tagMask |= tag;
}

void Entity::removeTag(ETag tag)
{
	m_tagMask &= !tag;
}

int Entity::getTagMask()
{
	return m_tagMask;
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
	//TODO: Remove, and give responsibility to application
	for (auto& component : m_components) {
		component->update(deltaTime);
	}
}

void Entity::draw(aie::Renderer2D * renderer)
{
	for (auto& component : m_components) {
		component->draw(renderer);
	}
}
