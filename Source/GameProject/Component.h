#pragma once

class Entity;

class Component
{
public:
	Component();
	virtual ~Component();

	virtual void update(Entity* entity, float deltaTime) = 0;

	virtual void draw(Entity* entity) {};

	virtual bool onAdd(Entity* entity);
	virtual void onRemove(Entity* entity);

	virtual int getID();

	enum Identifier {
		base,
		scene_object,
		sprite
	};
};

