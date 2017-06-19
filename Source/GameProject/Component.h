#pragma once
#include "Renderer2D.h"

class Entity;
typedef std::shared_ptr<Entity> EntityPtr;
typedef std::weak_ptr<Entity>	EntityWeakPtr;

class Component
{
public:
	Component();
	virtual ~Component();

	virtual void update(float deltaTime) = 0;

	virtual void draw(aie::Renderer2D* renderer) {};

	virtual bool onAdd(EntityPtr entity);
	virtual void onRemove(EntityPtr entity);

	
	enum Identifier {
		sprite = 0x1,
		collider = 0x2,
		controller = 0x4
	};

	virtual Identifier getID() = 0;
	
protected:
	EntityWeakPtr m_entity;
};

class missing_component : public std::logic_error {
public:
	explicit missing_component(const std::string& what_arg) : std::logic_error(what_arg)
	{};
	explicit missing_component(const char* what_arg) : std::logic_error(what_arg)
	{};

	virtual ~missing_component() {};
};