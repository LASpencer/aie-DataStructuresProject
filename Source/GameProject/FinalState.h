#pragma once
#include "GameState.h"
class FinalState :
	public GameState
{
public:
	FinalState(GameProjectApp* app);
	virtual ~FinalState();

	State* clone() const;

	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D* renderer);
};

