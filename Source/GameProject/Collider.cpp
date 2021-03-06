#include "stdafx.h"
#include "Collider.h"
#include "Entity.h"
#include "CollisionEvent.h"

bool Collider::draw_boxes = false;

Collider::Collider() : Component(), m_eventManager(this), m_localBoxes({}), m_globalBoxes({})
{
}


Collider::~Collider()
{
}

void Collider::setBoxes(las::Array<Box> boxes)
{
	m_localBoxes = boxes;
}

las::Array<Box> Collider::getLocalBoxes()
{
	return m_localBoxes;
}

las::Array<Box> Collider::getGlobalBoxes()
{
	return m_globalBoxes;
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

void Collider::update(float deltaTime)
{
	EntityPtr entity(m_entity);
	// Fill globalBoxes with copies of localBoxes
	m_globalBoxes.clear();
	for (Box local : m_localBoxes) {
		Box global = local;
		// Transform each corner by entity's position
		global.corner1 = glm::vec2(entity->getPosition()->getGlobalTransform() * glm::vec3(local.corner1.x, local.corner1.y, 1));
		global.corner2 = glm::vec2(entity->getPosition()->getGlobalTransform() * glm::vec3(local.corner2.x, local.corner2.y, 1));
		m_globalBoxes.push_back(global);
	}
}

void Collider::draw(aie::Renderer2D * renderer)
{
	if (draw_boxes) {
		EntityPtr entity(m_entity);
		for (Box box : m_globalBoxes) {
			// Calculate box's center and dimensions
			glm::vec2 center = 0.5f * (box.corner1 + box.corner2);
			float width = std::abs(box.corner1.x - box.corner2.x);
			float height = std::abs(box.corner1.y - box.corner2.y);
			// Set colour based on box type
			switch (box.type) {
			case(body):		//body is blue
				renderer->setRenderColour(0x0000FF80);
				break;
			case(feet):		//feet is purple
				renderer->setRenderColour(0xFF00FF80);
				break;
			case(attack):	//attack is red
				renderer->setRenderColour(0xFF000080);
				break;
			case(trigger):	//trigger is green
				renderer->setRenderColour(0x00FF0080);
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

void Collider::resolveCollisions(las::Array<std::shared_ptr<Collider>> colliders)
{
	las::Array<Collision> collisions{};		// Contains detected collisions
	size_t numColliders = colliders.size();
	// Get collisions between each pair
	for (size_t i = 0; i < numColliders; ++i) {
		for (size_t j = i+1; j < numColliders; ++j) {
			//Test collision between boxes
			for (Box box1 : colliders[i]->m_globalBoxes) {
				for (Box box2 : colliders[j]->m_globalBoxes) {
					std::pair<bool, glm::vec2> didCollide = testCollision(box1, box2);
					if (didCollide.first) {
						collisions.push_back({ {colliders[i],colliders[j]},{box1.type,box2.type},didCollide.second });
					}
				}
			}
		}
	}
	// For each collision, involved colliders notify observers
	for (Collision c : collisions) {
		CollisionEvent event1(c.collider[1]->getEntity(),c.type[0],c.type[1],c.penetration);
		CollisionEvent event2(c.collider[0]->getEntity(), c.type[1], c.type[0], -(c.penetration));
		c.collider[0]->notifyObservers(&event1);
		c.collider[1]->notifyObservers(&event2);
	}
}

std::pair<bool, glm::vec2> Collider::testCollision(Box box1, Box box2)
{
	float minX[2] = { std::min(box1.corner1.x, box1.corner2.x), std::min(box2.corner1.x, box2.corner2.x) };
	float maxX[2] = { std::max(box1.corner1.x, box1.corner2.x), std::max(box2.corner1.x, box2.corner2.x) };
	float minY[2] = { std::min(box1.corner1.y, box1.corner2.y), std::min(box2.corner1.y, box2.corner2.y) };
	float maxY[2] = { std::max(box1.corner1.y, box1.corner2.y), std::max(box2.corner1.y, box2.corner2.y) };
	//Check for overlap
	if (minX[0] >= maxX[1] ||
		minX[1] >= maxX[0] ||
		minY[0] >= maxY[1] ||
		minY[1] >= maxY[0]) {
		return std::make_pair(false, glm::vec2(0));
	} else {
		// Calculate penetration
		glm::vec2 penetration;
		float x, y;
		if (abs(maxX[1] - minX[0]) < abs(maxX[0] - minX[1])) {
			// box1 is on right
			x = maxX[1] - minX[0];
		} else {
			//box1 is on left
			x = minX[1] - maxX[0];
		}
		if (abs(maxY[1] - minY[0]) < abs(maxY[0] - minY[1])) {
			//box1 is above
			y = maxY[1] - minY[0];
		} else {
			//box1 is below
			y = minY[1] - maxY[0];
		}
		if (abs(x) < abs(y)) {
			penetration = { x,0 };
		} else {
			penetration = { 0, y };
		}
		return std::make_pair(true, penetration);
	}
}

void Collider::setDrawBoxes(bool shouldDraw)
{
	draw_boxes = shouldDraw;
}
