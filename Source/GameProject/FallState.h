#pragma once
#include "AirState.h"

class FallState :
	public AirState {
public:
	FallState(HeroController* controller);

	virtual ~FallState();

	virtual State* clone() const;

	virtual void onEnter();

	virtual void onExit();

	virtual void update(float deltaTime);

	virtual void draw(aie::Renderer2D* renderer);

	virtual void notify(Subject* subject, EventBase* event);
};