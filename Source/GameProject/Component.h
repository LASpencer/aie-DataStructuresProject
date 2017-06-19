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
		sprite = 1,
		collider = 2,
		physics = 4
	};

	virtual Identifier getID() = 0;
	
	
};

class missing_component : public std::invalid_argument {
public:
	explicit missing_component(const std::string& what_arg) : std::invalid_argument(what_arg)
	{};
	explicit missing_component(const char* what_arg) : std::invalid_argument(what_arg)
	{};

	virtual ~missing_component() {};
};