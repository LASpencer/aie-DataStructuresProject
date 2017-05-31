#include "stdafx.h"
#include "SceneObject.h"


SceneObject::SceneObject() : m_parent(), m_children(), m_localTransform(1),m_globalTransform(1),m_velocity(0),dirtyGlobal(true)
{
}


SceneObject::~SceneObject()
{
}

void SceneObject::update(Entity * entity, float deltaTime)
{
	//TODO automatically apply velocity and rotation(?)
	translate(m_velocity * deltaTime, false);
}

int SceneObject::getID()
{
	return Identifier::scene_object;
}

bool SceneObject::addChild(SceneObjectPtr child)
{
	if (child->m_parent.get() == nullptr && child.get() != this) {
		child->m_parent = SceneObjectPtr(this);
		child->dirtyGlobal = true;
		m_children.push_back(SceneObjectWeakPtr(child));
		return true;
	}
	return false;
}

void SceneObject::setLocalTransform(glm::mat3 local)
{
	m_localTransform = local;
	setDirty();
}

void SceneObject::setVelocity(glm::vec2 velocity)
{
	m_velocity = velocity;
}

void SceneObject::applyTransform(glm::mat3 transform, bool post)
{
	if (post) {
		m_localTransform = m_localTransform * transform;
	} else {
		m_localTransform = transform * m_localTransform;
	}
	setDirty();
}

void SceneObject::translate(glm::vec2 displacement, bool post)
{
	if (post) {
		m_localTransform = glm::translate(m_localTransform, displacement);
	} else {
		glm::mat3 translate = glm::translate(glm::mat3(1), displacement);
		m_localTransform = translate * m_localTransform;
	}
	setDirty();
}

void SceneObject::rotate(float angle, bool post)
{
	if (post) {
		m_localTransform = glm::rotate(m_localTransform, angle);
	} else{
		glm::mat3 rotation = glm::rotate(glm::mat3(1), angle);
	}
	setDirty();
}

void SceneObject::applyDeltaV(glm::vec2 deltaV, bool local)
{
	if (local) {
		glm::vec3 deltaV3(deltaV[0], deltaV[1], 0.0f);
		deltaV3 = m_localTransform * deltaV3;
		deltaV = (glm::vec2)deltaV3;
	}
	m_velocity += deltaV;
}

glm::mat3 SceneObject::getLocalTransform()
{
	return m_localTransform;
}

glm::mat3 SceneObject::getGlobalTransform()
{
	if (dirtyGlobal) {
		calculateGlobalTransform();
	}
	assert(!dirtyGlobal);
	return m_globalTransform;
}

void SceneObject::setDirty()
{
	dirtyGlobal = true;
	for (SceneObjectWeakPtr child : m_children) {
		if (!child.expired()) {
			SceneObjectPtr(child)->setDirty();
		}
	}
}

void SceneObject::calculateGlobalTransform()
{
	if (m_parent.get() == nullptr) {
		// If root, global is local
		m_globalTransform = m_localTransform;
	} else {
		m_globalTransform = m_parent->getGlobalTransform() * m_localTransform;
	}
	dirtyGlobal = false;
}
