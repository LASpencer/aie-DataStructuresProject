#pragma once
#include "HeroState.h"

class IdleState : public HeroState {

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