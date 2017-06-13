#include "stdafx.h"
#include "Hero.h"

las::Map<Hero::Stance, std::pair<float, float>> Hero::m_animationFrames;

Hero::Hero()
{
	setupFrames();
}

Hero::~Hero()
{
}

void Hero::update(float deltaTime)
{
	Entity::update(deltaTime);
}

void Hero::draw(aie::Renderer2D * renderer)
{
	Entity::draw(renderer);
}

void Hero::setupFrames()
{
	if (m_animationFrames.empty()) {
		m_animationFrames[idle] = { 0,0 };
		m_animationFrames[crouch] = { 0.125f,0 };
		m_animationFrames[wind_up] = { 0.25f,0 };
		m_animationFrames[strike_1] = { 0.375f,0 };
		m_animationFrames[strike_2] = { 0.5f,0 };
		m_animationFrames[wind_down] = { 0.625f, 0 };
		m_animationFrames[jump] = { 0.75f,0 };
		m_animationFrames[land] = { 0.875f,0 };
		m_animationFrames[hurt] = { 0,0.25f };
		m_animationFrames[crouch_hurt] = { 0.125f,0.25f };
		m_animationFrames[jump_wind_up] = { 0.25f,0.25f };
		m_animationFrames[jump_strike_1] = { 0.325f,0.25f };
		m_animationFrames[jump_strike_2] = { 0.5f,0.25f };
		m_animationFrames[jump_wind_down] = { 0.625f, 0.25f };
		m_animationFrames[falling] = { 0,0.5f };
		m_animationFrames[downed] = { 0.125f, 0.5f };
		m_animationFrames[crouch_wind_up] = { 0.25f,0.5f };
		m_animationFrames[crouch_strike_1] = { 0.325f,0.5f };
		m_animationFrames[crouch_strike_2] = { 0.5f,0.5f };
		m_animationFrames[crouch_wind_down] = { 0.625f, 0.5f };
		m_animationFrames[run] = { 0,0.75f };
	}
}
