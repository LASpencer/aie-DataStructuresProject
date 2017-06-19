#pragma once
#include "Component.h"
#include "Subject.h"
#include "EventManager.h"

enum BoxType {
	body,
	attack,
	trigger
};

struct Box {
	glm::vec2 corner1;
	glm::vec2 corner2;
	BoxType type;

};

class Collider :
	public Component, public Subject
{
public:
	Collider();
	virtual ~Collider();

	void setBoxes(las::Array<Box> boxes);
	las::Array<Box> getBoxes();

	virtual void addObserver(std::shared_ptr<Observer> observer);
	virtual void removeObserver(std::shared_ptr<Observer> observer);
	virtual void clearObservers();
	virtual void notifyObservers(EventBase* event);
	virtual bool isSubscribed(const Observer* observer) const;

	virtual void update(Entity* entity, float deltaTime);
	virtual void draw(Entity* entity, aie::Renderer2D* renderer);
	static const bool draw_boxes = true;

	virtual Identifier getID();

protected:
	EventManager m_eventManager;
	
	las::Array<Box> m_boxes;
};

