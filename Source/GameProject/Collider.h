#pragma once
#include "Defines.h"
#include "Component.h"
#include "Subject.h"
#include "EventManager.h"

/* Enumeration of different types of hitboxes
	Used to determine collision resolution*/
enum BoxType {
	body,		// Used for physical collisions
	feet,		// Used to test if entity is supported by a body
	attack,		// Used for attack hitboxes
	trigger		// Triggers some event when collided with
};

// A hitbox used for collision testing and resolution
struct Box {
	glm::vec2 corner1;
	glm::vec2 corner2;
	BoxType type;

};

class Collider;

typedef std::shared_ptr<Collider> ColliderPtr;
typedef std::weak_ptr<Collider>	ColliderWeakPtr;

// Contains data representing a collision between two hitboxes
struct Collision {
	std::shared_ptr<Collider>	collider[2];	// Colliders containing the boxes
	BoxType		type[2];						// Types of first and second box
	glm::vec2	penetration;		// Penetration of second box into first
};

/*	Component containing hitboxes, allowing entity to collide with other entities
	Collider is also a Subject, producing CollisionEvents when a collision occurs
	informing the Observers to respond appropriately.
*/
class Collider :
	public Component, public Subject
{
public:
	static bool draw_boxes;		//If true, display hitboxes coloured according to BoxType

	Collider();
	virtual ~Collider();

	void setBoxes(las::Array<Box> boxes);

	las::Array<Box> getLocalBoxes();
	las::Array<Box> getGlobalBoxes();

	//TODO comment these after Observer done
	virtual void addObserver(std::shared_ptr<Observer> observer);
	virtual void removeObserver(std::shared_ptr<Observer> observer);
	virtual void clearObservers();
	virtual void notifyObservers(EventBase* event);
	virtual bool isSubscribed(const Observer* observer) const;

	virtual void update(float deltaTime);	// does nothing

	/** If draw_boxes set to true, draw hitboxes
	*	@param renderer Renderer2D to draw boxes to*/
	virtual void draw(aie::Renderer2D* renderer);

	// Returns Collider identifier
	virtual Identifier getID();

	/**	Tests for collisions and has colliders involved produce collision events
	*	@param colliders Colliders being checked for collision*/
	static void resolveCollisions(las::Array <std::shared_ptr<Collider>> colliders);

	/** Tests whether boxes collide
	*	@param box1 first hitbox
	*	@param box2 second hitbox
	*	@return pair of whether collision occured and if so penetration of box2 into box1*/
	static std::pair<bool,glm::vec2> testCollision(Box box1, Box box2);

	static void setDrawBoxes(bool shouldDraw);

protected:
	EventManager m_eventManager;
	
	las::Array<Box> m_localBoxes;	// Hitboxes with position relative to entity's position
	las::Array<Box> m_globalBoxes;	// Hitboxes with global positon
};

