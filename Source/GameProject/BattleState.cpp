#include "stdafx.h"
#include "BattleState.h"
#include "GameProjectApp.h"

BattleState::BattleState(GameProjectApp* app) : GameState(app)
{
}


BattleState::~BattleState()
{
}

BattleState::BattleState(const BattleState & other) : GameState(other), m_battleImage(other.m_battleImage)
{
}

State * BattleState::clone() const
{
	return new BattleState(*this);
}

void BattleState::update(float deltaTime)
{
	//TODO game logic here
}

void BattleState::draw(aie::Renderer2D * renderer)
{
	renderer->drawSprite(m_battleImage->get(), 640, 360);
}

void BattleState::onEnter()
{
	GameState::onEnter();
	m_battleImage = m_app->getResourceManager()->getTexture("./textures/combatBG.png");
}
