#include "stdafx.h"
#include "BattleState.h"
#include "GameProjectApp.h"
#include "SceneObject.h"
#include "Sprite.h"
#include "Collider.h"
#include "Filepaths.h"

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
		las::Array<EntityPtr>::iterator first = m_app->getEntityList().begin();
		las::Array<EntityPtr>::iterator last = m_app->getEntityList().end();
		las::Array<EntityPtr> entitiesWithComponent = getEntitiesWithComponent(Component::controller, first, last);
		for (EntityPtr entity :entitiesWithComponent) {
			entity->getComponent(Component::controller)->update(deltaTime);
		}
		entitiesWithComponent = getEntitiesWithComponent(Component::collider, first, last);
		//TODO collision detection
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
	las::Array<EntityPtr>::iterator first = m_app->getEntityList().begin();
	las::Array<EntityPtr>::iterator last = m_app->getEntityList().end();
	las::Array<EntityPtr> entitiesWithComponent = getEntitiesWithComponent(Component::sprite, first, last);
	for (EntityPtr entity : entitiesWithComponent) {
		entity->getComponent(Component::sprite)->draw(renderer);
	}
	if (Collider::draw_boxes) {
		entitiesWithComponent = getEntitiesWithComponent(Component::collider, first, last);
		for (EntityPtr entity : entitiesWithComponent) {
			entity->getComponent(Component::collider)->draw(renderer);
		}
	}
}

void BattleState::onEnter()
{
	GameState::onEnter();
	//
	m_battleImage = m_app->getResourceManager()->getTexture(filepath::castle_background);
	m_app->getEntityFactory()->createEntity(EntityFactory::hero, { 1,0,0,0,1,0,300,405,1 });
	m_app->getEntityFactory()->createEntity(EntityFactory::block, { 1,0,0,0,1,0,600,395,1 });
	EntityPtr door = m_app->getEntityFactory()->createEntity(EntityFactory::door, { 1,0,0,0,1,0,1152,462,1 });
	m_app->getEntityFactory()->createEntity(EntityFactory::floor, { 1,0,0,0,1,0,640,360,1 });

	// Observe door collider to check for hero leaving
	std::dynamic_pointer_cast<Collider>(door->getComponent(Component::collider))->addObserver(shared_from_this());
}

void BattleState::onExit()
{
	//TODO cleanup unused resources
}

void BattleState::notify(Subject * subject, EventBase * event)
{
	//TODO if event is collision between hero's collider and door trigger, move to win screen
}

bool BattleState::addSubject(Subject * subject)
{
	return true;
}

void BattleState::removeSubject(Subject * subject)
{
}

las::Array<EntityPtr> BattleState::getEntitiesWithComponent(Component::Identifier component, las::Array<EntityPtr>::iterator first, las::Array<EntityPtr>::iterator last)
{
	//TODO AAAAAAAA use find_if to fill new array with all entities with matching bitmask
	las::Array<EntityPtr> entitiesWithComponent;
	auto maskMatches = [=](EntityPtr e) {return bool(component&(e->getComponentMask())); };
	las::Array<EntityPtr>::iterator entity = std::find_if(first, last, maskMatches);
	//TODO while entity not last, push entity into entitiesWithComponent and call find_if again
	//TODO put lambda into a variale, it's going to be reused
	while (entity != last) {
		entitiesWithComponent.push_back(*entity);
		entity = std::find_if(++entity, last, maskMatches);
	}
	return entitiesWithComponent;
}
