#pragma once
#include "HeroState.h"

class IdleState : public HeroState {

public:
	IdleState(Hero* hero);

	virtual ~IdleState();

	virtual State* clone() const;

	virtual void onEnter();

	virtual void onExit();

	virtual void update(float deltaTime);

	virtual void draw(aie::Renderer2D* renderer);
};