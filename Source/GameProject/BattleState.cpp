#include "stdafx.h"
#include "BattleState.h"
#include "GameProjectApp.h"

#include "Ship.h"
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
	ship->update(deltaTime);
}

void BattleState::draw(aie::Renderer2D * renderer)
{
	renderer->drawSprite(m_battleImage->get(), 640, 360);
	//HACK for testing
	ship->draw(renderer);
}

void BattleState::onEnter()
{
	GameState::onEnter();
	m_battleImage = m_app->getResourceManager()->getTexture("./textures/combatBG.png");

	//HACK just for testing
	ship = new Ship();
	std::shared_ptr<SceneObject> pos = std::make_shared<SceneObject>();
	pos->setLocalTransform(glm::mat3(1, 0, 1, 0, 1, 1, 300,200, 1));
	ship->addComponent(pos);
	std::shared_ptr<Sprite> sprite = std::make_shared <Sprite>(m_app->getResourceManager()->getTexture("./textures/ship.png"));
	ship->addComponent(sprite);
}

void BattleState::onExit()
{
	//HACK just for testing
	delete ship;
	ship = nullptr;
}
