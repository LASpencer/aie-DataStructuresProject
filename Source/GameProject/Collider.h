#pragma once
#include "Component.h"
#include "Subject.h"
#include "EventManager.h"

enum BoxType {
	body,
	feet,
	attack,
	trigger
};

struct Box {
	glm::vec2 corner1;
	glm::vec2 corner2;
	BoxType type;

};

class Collider;

struct Collision {
	std::shared_ptr<Collider>	collider[2];
	BoxType		type[2];
	glm::vec2	penetration;
};

class Collider :
	public Component, public Subject
{
public:
	static const bool draw_boxes = true;

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

protected:
	EventManager m_eventManager;
	
	las::Array<Box> m_boxes;
};

