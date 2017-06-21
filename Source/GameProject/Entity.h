#pragma once
#include "stdafx.h"
#include "Array.h"
#include "Renderer2D.h"
#include "Component.h"
#include "SceneObject.h"

class Entity;
typedef std::shared_ptr<Component> ComponentPtr;
typedef std::shared_ptr<Entity> EntityPtr;
typedef std::weak_ptr<Entity>	EntityWeakPtr;

class Entity : public std::enable_shared_from_this<Entity>
{
public:

	enum ETag {
		player = 0x1,
		floor = 0x2,
		door = 0x4
	};

	Entity();
	virtual ~Entity();

	bool addComponent(const ComponentPtr& component);

	bool removeComponent(Component::Identifier id);

	int getComponentMask();

	void addTag(ETag tag);

	void removeTag(ETag tag);

	int getTagMask();

	ComponentPtr getComponent(Component::Identifier id);

	SceneObjectPtr getPosition();

protected:
	las::Array<ComponentPtr> m_components; //HACK: A map might be better?
	int m_componentMask;
	int m_tagMask;
	SceneObjectPtr m_position;
};

