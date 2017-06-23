#pragma once
#include "HeroState.h"

class GroundState :
	public HeroState {
	//TODO check if feet touched ground last frame, if not go to FallState
	//other states derive from this, so can be partly abstract

public:
	GroundState(HeroController* controller);
	virtual ~GroundState();

	virtual void onEnter();

	virtual void onExit();

	virtual void update(float deltaTime);

	virtual void notify(Subject* subject, EventBase* event);

protected:
	bool m_onFloor;
};