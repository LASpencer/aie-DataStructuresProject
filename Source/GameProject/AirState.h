#pragma once
#include "HeroState.h"

/*	Abstract state for hero in air
	Moves hero by verticalSpeed, and applies downward acceleration to it*/
class AirState :
	public HeroState {

public:
	AirState(HeroController* controller);

	~AirState();

	virtual void onEnter();
	virtual void onExit();

	virtual void update(float deltaTime);

	// On collision, stop moving towards colliding entity
	virtual void notify(Subject* subject, EventBase* event);
};