#pragma once
#include "GroundState.h"

//TODO should descend from GroundState, which keeps track of whether feet touched ground last frame
class IdleState : public GroundState {

public:
	IdleState(HeroController* controller);

	virtual ~IdleState();

	virtual State* clone() const;

	virtual void onEnter();

	virtual void onExit();

	virtual void update(float deltaTime);

	virtual void draw(aie::Renderer2D* renderer);

	virtual void notify(Subject* subject, EventBase* event);
};