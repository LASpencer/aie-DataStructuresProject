#include "stdafx.h"
#include "BattleState.h"
#include "GameProjectApp.h"
#include "Hero.h"
#include "SceneObject.h"
#include "Sprite.h"

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
	m_hero->update(deltaTime);
}

void BattleState::draw(aie::Renderer2D * renderer)
{
	renderer->setUVRect(0, 0, 1, 1);
	renderer->drawSprite(m_battleImage->get(), 640, 360);
	//HACK for testing
	m_hero->draw(renderer);
}

void BattleState::onEnter()
{
	GameState::onEnter();
	m_battleImage = m_app->getResourceManager()->getTexture("./textures/combatBG.png");

	m_hero = new Hero(m_app->getResourceManager()->getTexture("./textures/player/player-spritemap-v9.png"));//TODO make a const
	std::dynamic_pointer_cast<SceneObject>(m_hero->getComponent(Component::scene_object))->setLocalTransform({ 1,0,0,0,1,0,300,300,1 });
}

void BattleState::onExit()
{
	//HACK just for testing
	delete m_hero;
	m_hero = nullptr;
}
