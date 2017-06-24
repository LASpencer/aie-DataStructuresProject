#pragma once
#include "AirState.h"

/*	Hero is falling down
	This can be entered either from reaching the top of a jump, or
	from a Ground state when the hero's feet did not touch the floor

	Exits to Idle when colliding with floor from above
*/
class FallState :
	public AirState {
public:
	FallState(HeroController* controller);

	virtual ~FallState();

	virtual void onEnter();

	virtual void onExit();

	virtual void update(float deltaTime);

	virtual void notify(Subject* subject, EventBase* event);
};