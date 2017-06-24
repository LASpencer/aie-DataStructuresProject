#pragma once
#include "GroundState.h"

/*	Hero is walking
	Hero moves forwards with walking animation
	
	Transition to Idle when no walking key pressed, Jump on pressing jump key,
	or Fall if not supported by floor
	*/
class WalkState : public GroundState {

public:
	WalkState(HeroController* controller);

	virtual ~WalkState();

	virtual State* clone() const;

	virtual void onEnter();

	virtual void onExit();

	// Turn in direction pressed, and move forward
	virtual void update(float deltaTime);

	virtual void draw(aie::Renderer2D* renderer);

	virtual void notify(Subject* subject, EventBase* event);

protected:
	float m_timer;
	size_t m_frame;
};