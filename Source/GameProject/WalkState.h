#pragma once
#include "HeroState.h"

class WalkState : public HeroState {
	/*TODO
	*		Move to JumpState on jump button pressed
	*		Move to AttackState on attack button pressed
	*		Move to HurtState on taking damage
	*		Maybe move to CrouchState on crouch press (possibly with slide?)
	*		Move to IdleState on release left/right buttons
	*/
public:
	WalkState(HeroController* controller);

	virtual ~WalkState();

	virtual State* clone() const;

	virtual void onEnter();

	virtual void onExit();

	virtual void update(float deltaTime);

	virtual void draw(aie::Renderer2D* renderer);

protected:
	float m_timer;
	size_t m_frame;
};