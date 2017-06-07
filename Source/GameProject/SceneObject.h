#pragma once
#include "stdafx.h"
#include "Component.h"
#include "Array.h"

class SceneObject;
typedef std::shared_ptr<SceneObject> SceneObjectPtr;
typedef std::weak_ptr<SceneObject> SceneObjectWeakPtr;

//TODO comment, test, document SceneObject
class SceneObject :
	public Component
{
public:
	SceneObject();
	//TODO deep copy children, shallow parent
	virtual ~SceneObject();

	void update(Entity* entity, float deltaTime);

	virtual Identifier getID();

	bool addChild(SceneObjectPtr child);

	void setLocalTransform(glm::mat3 local);

	void setVelocity(glm::vec2 velocity);
	void applyTransform(glm::mat3 transform, bool post = true);
	void translate(glm::vec2 translate, bool post = true);
	void rotate(float angle, bool post = true);
	void applyDeltaV(glm::vec2 deltaV, bool local = false);


	glm::mat3 getLocalTransform();
	glm::mat3 getGlobalTransform();

	void setDirty();

protected:
	SceneObjectPtr m_parent;
	las::Array<SceneObjectWeakPtr> m_children;
	glm::mat3 m_localTransform;
	glm::mat3 m_globalTransform;

	glm::vec2 m_velocity; //Velocity relative to parent

	bool dirtyGlobal;				//Set to true when globalTransform must be recalculated

	void calculateGlobalTransform();
};

