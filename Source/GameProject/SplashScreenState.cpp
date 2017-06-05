#include "stdafx.h"
#include "SplashScreenState.h"

const float SplashScreenState::TIMER_DURATION = 3.0f;

SplashScreenState::SplashScreenState() : GameState(), m_timer(0), m_splashImage()
{
}


SplashScreenState::~SplashScreenState()
{

}

SplashScreenState::SplashScreenState(const SplashScreenState & other) : GameState(other), m_timer(0)
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
			notifyObservers(timer_finished);//should have transition to main menu, with condition that timer_finished has fired
		}
	}
}

void SplashScreenState::draw(aie::Renderer2D* renderer)
{
	//TODO draw splashscreen image
	renderer->drawSprite(m_splashImage->get(), 640, 360);
}

void SplashScreenState::loadTextures(ResourceManager<aie::Texture>* textureManager)
{
	m_splashImage = textureManager->get("./textures/splashScreen.png");
}

void SplashScreenState::onEnter()
{
	GameState::onEnter();
	m_timer = 0;
	notifyObservers(timer_start);
}

