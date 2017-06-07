#pragma once
#include "Renderer2D.h"

class Entity;

class Component
{
public:
	Component();
	virtual ~Component();

	virtual void update(Entity* entity, float deltaTime) = 0;

	virtual void draw(Entity* entity, aie::Renderer2D* renderer) {};

	virtual bool onAdd(Entity* entity);
	virtual void onRemove(Entity* entity);

	enum Identifier {
		base,
		scene_object,
		sprite
	};

	virtual Identifier getID();
	
	
};

