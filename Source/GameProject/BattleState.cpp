#include "stdafx.h"
#include "BattleState.h"
#include "GameProjectApp.h"
#include "Hero.h"
#include "SceneObject.h"
#include "Sprite.h"

const aie::EInputCodes BattleState::pause_key = aie::INPUT_KEY_ESCAPE;

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
	if (m_focus) {
		//TODO update components as a group, from all entities with said component
		for (EntityPtr entity : m_app->getEntityList()) {
			entity->update(deltaTime);
		}
		if (aie::Input::getInstance()->wasKeyPressed(pause_key)) {
			m_shouldPush = true;
			m_target = GameStateMachine::pause_state;
		}
		//TODO transition win_screen if door reached
		//TODO transition game_over if hero dead
	}
}

void BattleState::draw(aie::Renderer2D * renderer)
{
	renderer->setUVRect(0, 0, 1, 1);
	renderer->drawSprite(m_battleImage->get(), 640, 360);
	//TODO just draw sprite components and (if activated) colliders
	for (EntityPtr entity : m_app->getEntityList()) {
		entity->draw(renderer);
	}
}

void BattleState::onEnter()
{
	GameState::onEnter();
	m_battleImage = m_app->getResourceManager()->getTexture("./textures/combatBG.png");
	m_app->getEntityFactory()->createEntity(EntityFactory::hero, { 1,0,0,0,1,0,300,300,1 });
	m_app->getEntityFactory()->createEntity(EntityFactory::block, { 1,0,0,0,1,0,600,330,1 });
}

void BattleState::onExit()
{
	//TODO cleanup unused resources
}
