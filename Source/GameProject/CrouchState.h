#pragma once
#include "GroundState.h"

/*	Hero is crouching
	Can transition to Jump (by pressing jump key), Idle (by releasing crouch key) 
	or Fall (if feet aren't touching a floor entity)
*/
class CrouchState : public GroundState {
public:

	CrouchState(HeroController* controller);

	virtual ~CrouchState();

	virtual State* clone() const;

	virtual void onEnter();

	virtual void onExit();

	virtual void update(float deltaTime);

	virtual void draw(aie::Renderer2D* renderer);

};