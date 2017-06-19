#include "stdafx.h"
#include "Component.h"


Component::Component()
{
}


Component::~Component()
{
}

bool Component::onAdd(Entity * entity)
{
	return true;
}

void Component::onRemove(Entity * entity)
{
}
