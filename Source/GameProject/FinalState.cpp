#include "stdafx.h"
#include "FinalState.h"
#include "GameProjectApp.h"

FinalState::FinalState(GameProjectApp* app) : GameState(app)
{
}


FinalState::~FinalState()
{
}

State * FinalState::clone() const
{
	return new FinalState(*this);
}

void FinalState::update(float deltaTime)
{
	// Quit the application
	m_app->quit();
}

void FinalState::draw(aie::Renderer2D * renderer)
{
}
