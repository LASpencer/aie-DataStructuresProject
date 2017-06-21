#include "stdafx.h"
#include "SceneObject.h"


SceneObject::SceneObject() : m_parent(), m_children(), m_localTransform(1),m_globalTransform(1),dirtyGlobal(true)
{
}


SceneObject::~SceneObject()
{
	//TODO fix sceneObject memory bug
}

void SceneObject::update(Entity * entity, float deltaTime)
{
}


bool SceneObject::addChild(SceneObjectPtr child)
{
	if (child->m_parent.get() == nullptr && child.get() != this) {
		// If array would be resized, try removing expired references instead
		if (m_children.size() == m_children.capacity()) {
			collectGarbage();
		}
		child->m_parent = SceneObjectPtr(shared_from_this());
		child->setDirty();
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

void SceneObject::collectGarbage()
{
	m_children.erase(std::remove_if(m_children.begin(), m_children.end(), 
		[](SceneObjectWeakPtr s) {return s.expired(); }), m_children.end());
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
