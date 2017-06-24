#include "stdafx.h"
#include "SplashScreenState.h"
#include "GameProjectApp.h"
#include "Event.h"
#include "Audio.h"
#include "Filepaths.h"

const float SplashScreenState::splash_duration = 5.f;

SplashScreenState::SplashScreenState(GameProjectApp* app) : GameState(app), m_timer(0), m_splashImage(), m_resourcesLoaded(false), m_splashShown(false)
{
}


SplashScreenState::~SplashScreenState()
{

}

SplashScreenState::SplashScreenState(const SplashScreenState & other) : GameState(other), m_timer(other.m_timer), m_splashImage(other.m_splashImage), m_resourcesLoaded(other.m_resourcesLoaded), m_splashShown(other.m_splashShown)
{
}

SplashScreenState & SplashScreenState::operator=(const SplashScreenState & other)
{
	GameState::operator=(other);
	m_timer = other.m_timer;
	m_resourcesLoaded = other.m_resourcesLoaded;
	m_splashShown = other.m_splashShown;
	return *this;
}

State * SplashScreenState::clone() const
{
	return new SplashScreenState(*this);
}

void SplashScreenState::update(float deltaTime)
{
	if (m_focus) {
		m_timer += deltaTime;
		if (m_timer > splash_duration) {
			m_shouldTransition = true;
			m_target = GameStateMachine::main_menu;
		}
		// Load resources now to avoid frame drops later
		if (m_timer > 0.1f && !m_resourcesLoaded) {
			AudioPtr audio = m_app->getResourceManager()->getAudio(filepath::win_music);
			audio = m_app->getResourceManager()->getAudio(filepath::castle_music);
			TexturePtr texture = m_app->getResourceManager()->getTexture(filepath::menu_background);
			texture = m_app->getResourceManager()->getTexture(filepath::castle_background);
			texture = m_app->getResourceManager()->getTexture(filepath::win_background);
			m_app->getEntityFactory()->loadResources();
			m_resourcesLoaded = true;
		}
	}
	//TODO load resources while waiting
}

void SplashScreenState::draw(aie::Renderer2D* renderer)
{
	//draw splashscreen image
	renderer->drawSprite(m_splashImage->get(), 640, 360);
	m_splashShown = true;
}


void SplashScreenState::onEnter()
{
	GameState::onEnter();
	AudioPtr m_music = m_app->getResourceManager()->getAudio(filepath::menu_music);
	m_music->get()->setLooping(true);
	if (!m_music->get()->getIsPlaying()) {
		m_music->get()->play();
	}
	m_splashImage = m_app->getResourceManager()->getTexture(filepath::splash_background);
	m_timer = 0;
	m_resourcesLoaded = m_splashShown = false;
}

void SplashScreenState::onExit()
{
	GameState::onExit();
}

