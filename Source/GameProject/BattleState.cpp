#include "stdafx.h"
#include "BattleState.h"
#include "GameProjectApp.h"
#include "SceneObject.h"
#include "Sprite.h"
#include "Collider.h"
#include "Filepaths.h"
#include "CollisionEvent.h"

const aie::EInputCodes BattleState::pause_key = aie::INPUT_KEY_ESCAPE;
const aie::EInputCodes BattleState::toggle_hitboxes_key = aie::INPUT_KEY_GRAVE_ACCENT;

BattleState::BattleState(GameProjectApp* app) : GameState(app)
{
}


BattleState::~BattleState()
{
}

BattleState::BattleState(const BattleState & other) : GameState(other), m_battleImage(other.m_battleImage)
{
}

BattleState & BattleState::operator=(const BattleState & other)
{
	GameState::operator=(other);
	m_battleImage = other.m_battleImage;
	return *this;
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
		// Test collisions
		entitiesWithComponent = getEntitiesWithComponent(Component::collider, first, last);
		las::Array<std::shared_ptr<Collider>> colliders;
		for (EntityPtr entity : entitiesWithComponent) {
			std::shared_ptr<Collider> collider = std::dynamic_pointer_cast<Collider>(entity->getComponent(Component::collider));
			collider->update(deltaTime);
			colliders.push_back(collider);
		}
		Collider::resolveCollisions(colliders);
		
		if (aie::Input::getInstance()->wasKeyPressed(pause_key)) {
			m_shouldPush = true;
			m_target = GameStateMachine::pause_state;
		}
		if (aie::Input::getInstance()->wasKeyPressed(toggle_hitboxes_key)) {
			Collider::setDrawBoxes(!Collider::draw_boxes);
		}
		//TODO transition game_over if hero dead
	}
}

void BattleState::draw(aie::Renderer2D * renderer)
{
	renderer->drawSprite(m_battleImage->get(), 640, 360);
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
	m_app->getEntityFactory()->createEntity(EntityFactory::block, { 1,0,0,0,1,0,200,395,1 });
	EntityPtr door = m_app->getEntityFactory()->createEntity(EntityFactory::door, { 1,0,0,0,1,0,1152,462,1 });
	m_app->getEntityFactory()->createEntity(EntityFactory::floor, { 1,0,0,0,1,0,640,360,1 });
	m_app->getEntityFactory()->createEntity(EntityFactory::hero, { 1,0,0,0,1,0,300,405,1 });

	// Observe door collider to check for hero leaving
	std::dynamic_pointer_cast<Collider>(door->getComponent(Component::collider))->addObserver(shared_from_this());
}

void BattleState::onExit()
{
	//TODO if creation of entities moved, move this too
	m_app->getEntityList().clear();
}

void BattleState::notify(Subject * subject, EventBase * event)
{
	//TODO if event is collision between hero's collider and door trigger, move to win screen
	if (event->getEventID() == EventBase::collision) {
		CollisionEvent* collision = dynamic_cast<CollisionEvent*>(event);
		assert(collision != nullptr);
		Collider* collider = dynamic_cast<Collider*>(subject);
		if (collider != nullptr) {
			EntityPtr subjectEntity = EntityPtr(collider->getEntity());
			EntityPtr otherEntity = EntityPtr(collision->getOtherEntity());
			//Check that collision was trigger to body
			bool triggerToBody = (collision->getMyType() == BoxType::trigger) && (collision->getOtherType() == BoxType::body);
			//Check collider is door and other is player
			bool doorToPlayer = (subjectEntity->getTagMask() & Entity::door) && (otherEntity->getTagMask() & Entity::player);
			if (triggerToBody && doorToPlayer) {
				m_shouldTransition = true;
				m_target = GameStateMachine::win_state;
			}
		} else{
			throw std::invalid_argument("Only Collider subjects should produce collision events");
		}
	}
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
