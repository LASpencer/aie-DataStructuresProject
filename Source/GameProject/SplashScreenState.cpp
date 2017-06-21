#include "stdafx.h"
#include "SplashScreenState.h"
#include "GameProjectApp.h"
#include "Event.h"
#include "Filepaths.h"

const float SplashScreenState::TIMER_DURATION = 1.5f;

SplashScreenState::SplashScreenState(GameProjectApp* app) : GameState(app), m_timer(0), m_splashImage()
{
}


SplashScreenState::~SplashScreenState()
{

}

SplashScreenState::SplashScreenState(const SplashScreenState & other) : GameState(other), m_timer(0), m_splashImage(other.m_splashImage)
{
}

State * SplashScreenState::clone() const
{
	return new SplashScreenState(*this);
}

void SplashScreenState::update(float deltaTime)
{
	if (m_focus) {
		m_timer += deltaTime;
		if (m_timer > TIMER_DURATION) {
			m_shouldTransition = true;
			m_target = GameStateMachine::main_menu;
		}
	}
	//TODO load resources while waiting
}

void SplashScreenState::draw(aie::Renderer2D* renderer)
{
	//TODO draw splashscreen image
	renderer->drawSprite(m_splashImage->get(), 640, 360);
}


void SplashScreenState::onEnter()
{
	GameState::onEnter();
	m_splashImage = m_app->getResourceManager()->getTexture(filepath::splash_background);
	m_timer = 0;
	Event timerStart(EventBase::timer_start);
	notifyObservers(&timerStart);
}

