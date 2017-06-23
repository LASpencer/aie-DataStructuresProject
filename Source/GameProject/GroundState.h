#pragma once
#include "HeroState.h"

/*	Abstract base state for any state on the ground
	Checks whether feet hitbox touched a floor since last update.
	*/
class GroundState :
	public HeroState {

public:
	GroundState(HeroController* controller);
	virtual ~GroundState();

	// Sets m_onFloor to true
	virtual void onEnter();

	virtual void onExit();

	// Resets m_onFloor to false
	virtual void update(float deltaTime);

	/*	If notified of collision between hero's feet and floor
		sets m_onFloor to true
	*/
	virtual void notify(Subject* subject, EventBase* event);

protected:
	bool m_onFloor;
};