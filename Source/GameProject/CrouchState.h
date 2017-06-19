#pragma once
#include "HeroState.h"

class CrouchState : public HeroState {
public:
	/*TODO	Moves to IdleState on release crouch button
	*		Moves to CrouchAttackState on pressing attack button
	*		Moves to JumpState on pressing jump button
	*		Moves to CrouchHurtState on taking damage
	*/
	//TODO: Maybe allow slides while crouched?

	CrouchState(Hero* hero);

	virtual ~CrouchState();

	virtual State* clone() const;

	virtual void onEnter();

	virtual void onExit();

	virtual void update(float deltaTime);

	virtual void draw(aie::Renderer2D* renderer);

};