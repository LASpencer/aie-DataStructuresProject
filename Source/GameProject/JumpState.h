#pragma once
#include "AirState.h"
//TODO add FallingState
class JumpState : public AirState {
	/*TODO	Moves to FallState if velocity <0
	*		Moves to AerialAttackState on pressing attack button
	*		Moves to AerialHurtState on taking damage
	*/
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