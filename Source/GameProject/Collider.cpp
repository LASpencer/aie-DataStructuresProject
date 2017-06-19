#include "stdafx.h"
#include "Collider.h"
#include "Entity.h"

Collider::Collider() : m_eventManager(this)
{
}


Collider::~Collider()
{
}

void Collider::setBoxes(las::Array<Box> boxes)
{
	m_boxes = boxes;
}

las::Array<Box> Collider::getBoxes()
{
	return m_boxes;
}

void Collider::addObserver(std::shared_ptr<Observer> observer)
{
	m_eventManager.addObserver(observer);
}

void Collider::removeObserver(std::shared_ptr<Observer> observer)
{
	m_eventManager.removeObserver(observer);
}

void Collider::clearObservers()
{
	m_eventManager.clearObservers();
}

void Collider::notifyObservers(EventBase * event)
{
	m_eventManager.notifyObservers(event);
}

bool Collider::isSubscribed(const Observer * observer) const
{
	return m_eventManager.isSubscribed(observer);
}

void Collider::update(Entity * entity, float deltaTime)
{
}

void Collider::draw(Entity * entity, aie::Renderer2D * renderer)
{
	if (draw_boxes) {
		for (Box box : m_boxes) {
			glm::vec2 corner1( entity->getPosition()->getGlobalTransform() * glm::vec3(box.corner1.x, box.corner1.y, 1));
			glm::vec2 corner2(entity->getPosition()->getGlobalTransform() * glm::vec3(box.corner2.x, box.corner2.y, 1));
			glm::vec2 center = 0.5f * (corner1 + corner2);
			float width = std::abs(corner1.x - corner2.x);
			float height = std::abs(corner1.y - corner2.y);
			switch (box.type) {
			case(body):
				renderer->setRenderColour(0x0000FF88);
				break;
			case(attack):
				renderer->setRenderColour(0xFF000088);
				break;
			case(trigger):
				renderer->setRenderColour(0x00FF0088);
				break;
			default:
				break;
			}
			renderer->drawBox(center.x, center.y, width, height);
		}
	}
}

Collider::Identifier Collider::getID()
{
	return collider;
}
