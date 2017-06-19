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
		//TODO game logic here
		m_hero->update(deltaTime);
		if (aie::Input::getInstance()->wasKeyPressed(pause_key)) {
			m_shouldPush = true;
			m_target = GameStateMachine::pause_state;
		}
		//TODO transition win_screen if all enemies dead
		//TODO transition game_over if hero dead
	}
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

	//TODO move this out to a Creature Factory class
	las::Array<TexturePtr> textures({	m_app->getResourceManager()->getTexture(Hero::sprite_filepath),
										m_app->getResourceManager()->getTexture(Hero::robe_filepath), 
										m_app->getResourceManager()->getTexture(Hero::armour_filepath),
										m_app->getResourceManager()->getTexture(Hero::helmet_filepath),
										m_app->getResourceManager()->getTexture(Hero::shield_filepath) });
	m_hero = new Hero(textures);//TODO make a const
	m_hero->getPosition()->setLocalTransform({ 1,0,0,0,1,0,300,300,1 });
}

void BattleState::onExit()
{
	//HACK just for testing
	delete m_hero;
	m_hero = nullptr;
}
