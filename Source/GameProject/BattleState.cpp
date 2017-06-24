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
		// Update controller components
		las::Array<EntityPtr> entitiesWithComponent = Entity::getEntitiesWithComponent(Component::controller, m_app->getEntityList());
		for (EntityPtr entity :entitiesWithComponent) {
			entity->getComponent(Component::controller)->update(deltaTime);
		}
		// Update colliders and test collision
		entitiesWithComponent = Entity::getEntitiesWithComponent(Component::collider, m_app->getEntityList());
		las::Array<std::shared_ptr<Collider>> colliders;
		for (EntityPtr entity : entitiesWithComponent) {
			std::shared_ptr<Collider> collider = std::dynamic_pointer_cast<Collider>(entity->getComponent(Component::collider));
			collider->update(deltaTime);
			colliders.push_back(collider);
		}
		Collider::resolveCollisions(colliders);
		
		// Check for pause or turning on debug mode
		if (aie::Input::getInstance()->wasKeyPressed(pause_key)) {
			m_shouldPush = true;
			m_target = GameStateMachine::pause_state;
		}
		if (aie::Input::getInstance()->wasKeyPressed(toggle_hitboxes_key)) {
			Collider::setDrawBoxes(!Collider::draw_boxes);
		}
	}
}

void BattleState::draw(aie::Renderer2D * renderer)
{
	// Draw background
	renderer->drawSprite(m_battleImage->get(), 640, 360);
	// Draw sprites
	las::Array<EntityPtr> entitiesWithComponent = Entity::getEntitiesWithComponent(Component::sprite, m_app->getEntityList());
	for (EntityPtr entity : entitiesWithComponent) {
		entity->getComponent(Component::sprite)->draw(renderer);
	}
	// If enabled, draw hitboxes
	if (Collider::draw_boxes) {
		entitiesWithComponent = Entity::getEntitiesWithComponent(Component::collider, m_app->getEntityList());
		for (EntityPtr entity : entitiesWithComponent) {
			entity->getComponent(Component::collider)->draw(renderer);
		}
	}
}

void BattleState::onEnter()
{
	GameState::onEnter();
	m_music = m_app->getResourceManager()->getAudio(filepath::castle_music);
	m_music->get()->setLooping(true);
	if (!m_music->get()->getIsPlaying()) {
		m_music->get()->play();
	}
	// Load background from resource manager
	m_battleImage = m_app->getResourceManager()->getTexture(filepath::castle_background);
	// Create all entities needed for game
	m_app->getEntityFactory()->createEntity(EntityFactory::block, { 1,0,0,0,1,0,200,395,1 });
	m_app->getEntityFactory()->createEntity(EntityFactory::block, { 1,0,0,0,1,0,600,395,1 });
	m_app->getEntityFactory()->createEntity(EntityFactory::block, { 1,0,0,0,1,0,900,395,1 });
	m_app->getEntityFactory()->createEntity(EntityFactory::block, { 1,0,0,0,1,0,950,395,1 });
	m_app->getEntityFactory()->createEntity(EntityFactory::block, { 1,0,0,0,1,0,900,450,1 });
	m_app->getEntityFactory()->createEntity(EntityFactory::platform, {1,0,0,0,1,0,720,480,1});
	EntityPtr door = m_app->getEntityFactory()->createEntity(EntityFactory::door, { 1,0,0,0,1,0,1152,462,1 });
	m_app->getEntityFactory()->createEntity(EntityFactory::floor, { 1,0,0,0,1,0,640,360,1 });
	//Place hero last so they appear over other sprites
	m_app->getEntityFactory()->createEntity(EntityFactory::hero, { 1,0,0,0,1,0,300,800,1 });
	// Observe door collider to check for hero leaving
	std::dynamic_pointer_cast<Collider>(door->getComponent(Component::collider))->addObserver(shared_from_this());
}

void BattleState::onExit()
{
	GameState::onExit();
	GameState::onExit();
	m_music->get()->stop();
	// Destroy entities
	m_app->getEntityList().clear();
}

void BattleState::onFocus()
{
	GameState::onFocus();
	m_music->get()->play();
}

void BattleState::onLoseFocus()
{
	GameState::onLoseFocus();
	m_music->get()->pause();
}

void BattleState::notify(Subject * subject, EventBase * event)
{
	// If collision between player and door, transition to win state
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
