#include "stdafx.h"
#include "Component.h"


Component::Component() : m_entity()
{
}


Component::~Component()
{
}

bool Component::onAdd(EntityPtr entity)
{
	if (m_entity.expired()) {
		m_entity = EntityWeakPtr(entity);
		return true;
	}
	else {
		return false;
	}
}

void Component::onRemove(EntityPtr entity)
{
	m_entity = EntityWeakPtr();
}

