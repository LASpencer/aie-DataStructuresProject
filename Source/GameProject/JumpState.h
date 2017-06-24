#pragma once
#include "AirState.h"

/*	Hero is jumping
	Entered on pressing Jump key.
	Exits to Fall state after vertical speed reaches 0
*/
class JumpState 
	: public AirState {
public:
	JumpState(HeroController* controller);

	virtual ~JumpState();

	virtual State* clone() const;

	virtual void onEnter();

	virtual void onExit();

	virtual void update(float deltaTime);

	virtual void draw(aie::Renderer2D* renderer);

	virtual void notify(Subject* subject, EventBase* event);
};