#pragma once
#include "Defines.h"
#include "Component.h"
#include "Subject.h"
#include "EventManager.h"

enum BoxType {
	body,		// Used for physical collisions
	feet,		// Used to test if entity is supported by a body
	attack,		// Used for attack hitboxes
	trigger		// Triggers some event when collided with
};

struct Box {
	glm::vec2 corner1;
	glm::vec2 corner2;
	BoxType type;

};

class Collider;

typedef std::shared_ptr<Collider> ColliderPtr;
typedef std::weak_ptr<Collider>	ColliderWeakPtr;

struct Collision {
	std::shared_ptr<Collider>	collider[2];
	BoxType		type[2];
	glm::vec2	penetration;
};

class Collider :
	public Component, public Subject
{
public:

	static bool draw_boxes;

	Collider();
	virtual ~Collider();

	void setBoxes(las::Array<Box> boxes);
	las::Array<Box> getBoxes();

	virtual void addObserver(std::shared_ptr<Observer> observer);
	virtual void removeObserver(std::shared_ptr<Observer> observer);
	virtual void clearObservers();
	virtual void notifyObservers(EventBase* event);
	virtual bool isSubscribed(const Observer* observer) const;

	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D* renderer);

	virtual Identifier getID();

	static void resolveCollisions(las::Array <std::shared_ptr<Collider>> colliders);

	static std::pair<bool,glm::vec2> testCollision(Box box1, Box box2);

	static void setDrawBoxes(bool shouldDraw);

protected:
	EventManager m_eventManager;
	
	las::Array<Box> m_boxes;
};

