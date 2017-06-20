#include "stdafx.h"
#include "Filepaths.h"
#include "Hero.h"
#include "ResourceManager.h"
#include "SceneObject.h"
#include "Sprite.h"
#include "MultiSprite.h"
#include "Collider.h"
//
//las::Map<Hero::Stance, std::pair<float, float>> Hero::m_animationFrames;
//
//const float Hero::sprite_width = 46.0f;
//const float Hero::sprite_height = 50.0f;
//const float Hero::sprite_uv_width = 0.125f;
//const float Hero::sprite_uv_height = 0.25f;
//
//const float Hero::move_speed = 50.0f;
//const float Hero::move_frame_length = 0.1f;
//
//const std::string Hero::sprite_filepath = filepath::hero_blue;
//const std::string Hero::robe_filepath = filepath::robe_brown;
//const std::string Hero::armour_filepath = filepath::armour_samurai;
//const std::string Hero::shield_filepath = filepath::shield_zulu;
//const std::string Hero::helmet_filepath = filepath::helmet_gold;
//const std::string Hero::sword_filepath = filepath::sword_rapier;
//
//Hero::Hero() : Entity(), m_stateMachine(this)
//{ 
//	//TODO extract into init function
//	setupFrames();
//	std::pair<float, float> startFrame = m_animationFrames.at(idle);
//	addComponent(std::make_shared<MultiSprite>(las::Array<TexturePtr>(), sprite_width,sprite_height, startFrame.first,startFrame.second,sprite_uv_width,sprite_uv_height));
//	addComponent(std::make_shared<Collider>());
//	m_stateMachine.forceState(HeroStateMachine::idle_state);
//}
//
////TODO rewrite this
//Hero::Hero(las::Array<TexturePtr>& textures) : Entity(), m_stateMachine(this)
//{
//	setupFrames();
//	std::pair<float, float> startFrame = m_animationFrames.at(idle);
//	addComponent(std::make_shared<MultiSprite>(textures, sprite_width, sprite_height, startFrame.first, startFrame.second, sprite_uv_width, sprite_uv_height));
//	addComponent(std::make_shared<Collider>());
//	m_stateMachine.forceState(HeroStateMachine::idle_state);
//}
//
//Hero::~Hero()
//{
//}
//
//void Hero::update(float deltaTime)
//{
//	m_stateMachine.update(deltaTime);
//	Entity::update(deltaTime);
//}
//
//void Hero::draw(aie::Renderer2D * renderer)
//{
//	m_stateMachine.draw(renderer);
//	Entity::draw(renderer);
//}
//
//void Hero::setupFrames()
//{
//	if (m_animationFrames.empty()) {
//		m_animationFrames[idle] = { 0,0 };
//		m_animationFrames[crouch] = { 0.125f,0 };
//		m_animationFrames[wind_up] = { 0.25f,0 };
//		m_animationFrames[strike_1] = { 0.375f,0 };
//		m_animationFrames[strike_2] = { 0.5f,0 };
//		m_animationFrames[wind_down] = { 0.625f, 0 };
//		m_animationFrames[jump] = { 0.75f,0 };
//		m_animationFrames[land] = { 0.875f,0 };
//		m_animationFrames[hurt] = { 0,0.25f };
//		m_animationFrames[crouch_hurt] = { 0.125f,0.25f };
//		m_animationFrames[jump_wind_up] = { 0.25f,0.25f };
//		m_animationFrames[jump_strike_1] = { 0.325f,0.25f };
//		m_animationFrames[jump_strike_2] = { 0.5f,0.25f };
//		m_animationFrames[jump_wind_down] = { 0.625f, 0.25f };
//		m_animationFrames[falling] = { 0,0.5f };
//		m_animationFrames[downed] = { 0.125f, 0.5f };
//		m_animationFrames[crouch_wind_up] = { 0.25f,0.5f };
//		m_animationFrames[crouch_strike_1] = { 0.325f,0.5f };
//		m_animationFrames[crouch_strike_2] = { 0.5f,0.5f };
//		m_animationFrames[crouch_wind_down] = { 0.625f, 0.5f };
//		m_animationFrames[run1] = { 0,0.75f };
//		m_animationFrames[run2] = { 0.125f,0.75f };
//		m_animationFrames[run3] = { 0.25f,0.75f };
//		m_animationFrames[run4] = { 0.375f,0.75f };
//		m_animationFrames[run5] = { 0.5f,0.75f };
//		m_animationFrames[run6] = { 0.625f,0.75f };
//		m_animationFrames[run7] = { 0.75f,0.75f };
//		m_animationFrames[run8] = { 0.875f,0.75f };
//	}
//}
//
//void Hero::setStance(Stance stance)
//{
//	assert(m_componentMask & Component::sprite);
//	std::pair<float, float> UVpos = m_animationFrames[stance];
//	std::dynamic_pointer_cast<MultiSprite>(getComponent(Component::sprite))->setUVRect(UVpos.first, UVpos.second, sprite_uv_width, sprite_uv_height);
//	//TODO change collider based on stance
//	//TODO get rid of magic numbers
//	las::Array<Box> hitbox;
//	switch (stance) {
//	case(strike_1):
//	case(strike_2):
//	case(jump_strike_1):
//	case(jump_strike_2):
//		//TODO hurtbox from weapon
//	case(idle):
//	case(jump):
//	case(land):
//	case(wind_up):
//	case(wind_down):
//	case(jump_wind_up):
//	case(jump_wind_down):
//	case(hurt):
//	case(falling):
//	case(run1):
//	case(run2):
//	case(run3):
//	case(run4):
//	case(run5):
//	case(run6):
//	case(run7):
//	case(run8):
//		hitbox.push_back({ {-8,-23},{8,23},BoxType::body });
//		break;
//	case(crouch_strike_1):
//	case(crouch_strike_2):
//		//TODO hurtbox from weapon
//	case(crouch):
//	case(crouch_wind_up):
//	case(crouch_wind_down):
//	case(crouch_hurt):
//		hitbox.push_back({ {-8,-23},{8,8},BoxType::body });
//		break;
//	case(downed):
//		hitbox.push_back({ { -11,-23 },{ 11,-4 },BoxType::body });
//		break;
//	}
//	std::dynamic_pointer_cast<Collider>(getComponent(Component::collider))->setBoxes(hitbox);
//}
