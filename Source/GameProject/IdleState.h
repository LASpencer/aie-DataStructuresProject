#pragma once
#include "GroundState.h"

/*	Hero is not doing anything
	Can transition to Jump, Crouch, or Walk states though input,
	or to Fall state if feet are not supported by floor
*/
class IdleState 
	: public GroundState {

public:
	IdleState(HeroController* controller);

	virtual ~IdleState();

	virtual State* clone() const;

	virtual void onEnter();

	virtual void onExit();

	virtual void update(float deltaTime);

	virtual void notify(Subject* subject, EventBase* event);
};