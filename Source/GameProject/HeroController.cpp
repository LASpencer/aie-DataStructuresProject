#include "stdafx.h"
#include "HeroController.h"
#include "Collider.h"
#include "SpriteBase.h"
#include "Entity.h"

const float HeroController::sprite_uv_width = 0.125f;
const float HeroController::sprite_uv_height = 0.25f;

const las::Map < HeroController::Stance, std::pair<float, float>> 
	HeroController::animation_frames = {
	{ HeroController::idle, {0,0}},
	{HeroController::crouch, { 0.125f,0 }},
	{HeroController::wind_up, { 0.25f,0 }},
	{HeroController::strike_1, { 0.375f,0 }},
	{HeroController::strike_2, { 0.5f,0 }},
	{HeroController::wind_down, { 0.625f, 0 }},
	{HeroController::jump, { 0.75f,0 }},
	{HeroController::land, { 0.875f,0 }},
	{HeroController::hurt, { 0,0.25f }},
	{HeroController::crouch_hurt, { 0.125f,0.25f }},
	{HeroController::jump_wind_up, { 0.25f,0.25f }},
	{HeroController::jump_strike_1, { 0.325f,0.25f }},
	{HeroController::jump_strike_2, { 0.5f,0.25f }},
	{HeroController::jump_wind_down, { 0.625f, 0.25f }},
	{HeroController::falling, { 0,0.5f }},
	{HeroController::downed, { 0.125f, 0.5f }},
	{HeroController::crouch_wind_up, { 0.25f,0.5f }},
	{HeroController::crouch_strike_1, { 0.325f,0.5f }},
	{HeroController::crouch_strike_2, { 0.5f,0.5f }},
	{HeroController::crouch_wind_down, { 0.625f, 0.5f }},
	{HeroController::run1, { 0,0.75f }},
	{HeroController::run2, { 0.125f,0.75f }},
	{HeroController::run3, { 0.25f,0.75f }},
	{HeroController::run4, { 0.375f,0.75f }},
	{HeroController::run5, { 0.5f,0.75f }},
	{HeroController::run6, { 0.625f,0.75f }},
	{HeroController::run7, { 0.75f,0.75f }},
	{HeroController::run8, { 0.875f,0.75f }}
};

const Box HeroController::stand_hitbox = { { -16,-46 },{ 16,46 },BoxType::body };
const Box HeroController::run_hitbox = { { -16,-46 },{ 28,46 },BoxType::body };
const Box HeroController::crouch_hitbox = { { -16,-46 },{ 22,16 },BoxType::body };
const Box HeroController::downed_hitbox = { { -22,-46 },{ 22,-8 },BoxType::body };

const Box HeroController::stand_feetbox = { {-16,-50},{16,-46},BoxType::feet };
const Box HeroController::run_feetbox = { { -16,-50 },{ 28,-46 },BoxType::feet };
const Box HeroController::crouch_feetbox = { { -16,-50 },{ 22,-46 },BoxType::feet };
const Box HeroController::downed_feetbox = { { -22,-50 },{ 22,-46 },BoxType::feet };

const float HeroController::move_speed = 100.0f;
const float HeroController::move_frame_length = 0.1f;

HeroController::HeroController() : Controller(), m_stateMachine(this)
{
	m_stateMachine.forceState(HeroStateMachine::idle_state);
}

HeroController::~HeroController()
{
}

void HeroController::update(float deltaTime)
{
	EntityPtr entity(m_entity);
	if (!((entity->getComponentMask()&Component::sprite) && (entity->getComponentMask()&Component::collider))) {
		throw missing_component("HeroController requires Sprite and Collider components");
	}
	m_stateMachine.update(deltaTime);
}

void HeroController::draw(aie::Renderer2D * renderer)
{
	EntityPtr entity(m_entity);
	if (!((entity->getComponentMask()&Component::sprite) && (entity->getComponentMask()&Component::collider))) {
		throw missing_component("HeroController requires Sprite and Collider components");
	}
	m_stateMachine.draw(renderer);
}

bool HeroController::onAdd(EntityPtr entity)
{
	//TODO test that entity has correct bitmask (sprites, collider)
	bool added = Controller::onAdd(entity);
	if (added) {
		m_stateMachine.setHero(entity);
		//Watch hero's collider
		std::dynamic_pointer_cast<Collider>(entity->getComponent(Component::collider))->addObserver(shared_from_this());
	}
	return added;
}

void HeroController::onRemove(EntityPtr entity)
{
	Controller::onRemove(entity);
	std::shared_ptr<Collider> collider = std::dynamic_pointer_cast<Collider>(entity->getComponent(Component::collider));
	if (collider) {
		collider->removeObserver(shared_from_this());
	}
}

void HeroController::setStance(Stance stance)
{
	//TODO check entity bitmask
	EntityPtr entity(m_entity);
	std::pair<float, float> UVpos = animation_frames.at(stance);
	std::dynamic_pointer_cast<SpriteBase>(entity->getComponent(sprite))->setUVRect(UVpos.first, UVpos.second, sprite_uv_width, sprite_uv_height);
	//Set hitbox
	las::Array<Box> hitbox;
	switch (stance) {
	case(strike_1):
	case(strike_2):
	case(jump_strike_1):
	case(jump_strike_2):
		//TODO hurtbox from weapon
		//Fall through to get hitbox
	case(idle):
	case(jump):
	case(land):
	case(wind_up):
	case(wind_down):
	case(jump_wind_up):
	case(jump_wind_down):
	case(hurt):
	case(falling):
		hitbox.push_back(stand_hitbox);
		hitbox.push_back(stand_feetbox);
		break;
	case(run1):
	case(run2):
	case(run3):
	case(run4):
	case(run5):
	case(run6):
	case(run7):
	case(run8):
		hitbox.push_back(run_hitbox);
		hitbox.push_back(run_feetbox);
		break;
	case(crouch_strike_1):
	case(crouch_strike_2):
		//TODO hurtbox from weapon
		//Fall through to get hitbox
	case(crouch):
	case(crouch_wind_up):
	case(crouch_wind_down):
	case(crouch_hurt):
		hitbox.push_back(crouch_hitbox);
		hitbox.push_back(crouch_feetbox);
		break;
	case(downed):
		hitbox.push_back(downed_hitbox);
		hitbox.push_back(downed_feetbox);
		break;
	default:
		break;
	}
	std::dynamic_pointer_cast<Collider>(entity->getComponent(Component::collider))->setBoxes(hitbox);
}

bool HeroController::addSubject(Subject * subject)
{
	return true;
}

void HeroController::removeSubject(Subject * subject)
{
}

void HeroController::notify(Subject * subject, EventBase * event)
{
	//Pass event on to current state
	m_stateMachine.getState()->notify(subject, event);
}
