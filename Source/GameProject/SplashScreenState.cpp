#include "stdafx.h"
#include "SplashScreenState.h"
#include "GameProjectApp.h"
#include "Event.h"
#include "Audio.h"
#include "Input.h"
#include "Filepaths.h"

const float SplashScreenState::splash_duration = 5.f;
const float SplashScreenState::load_pos_x = 640.f;
const float SplashScreenState::load_pos_y = 100.f;
const unsigned short SplashScreenState::load_font_height = 16;

const std::string SplashScreenState::load_bg_msg = "Loading Background Textures";
const std::string SplashScreenState::load_sprite_msg = "Loading Sprites";
const std::string SplashScreenState::load_audio_msg = "Loading Audio";
const std::string SplashScreenState::load_done_msg = "Press any key to skip";

SplashScreenState::SplashScreenState(GameProjectApp* app) : GameState(app), m_timer(0), m_splashImage(), m_audioLoaded(false), m_backgroundLoaded(false), m_spritesLoaded(false)
{
	FontPtr loadFont = m_app->getResourceManager()->getFont(filepath::consolas_path, load_font_height);
	m_loadText = std::make_unique<TextBar>(loadFont, load_bg_msg, load_pos_x, load_pos_y, 0x00DD00FF, 0x00000040);
}


SplashScreenState::~SplashScreenState()
{

}

SplashScreenState::SplashScreenState(const SplashScreenState & other) : GameState(other),
m_timer(other.m_timer), m_splashImage(other.m_splashImage), m_audioLoaded(other.m_audioLoaded),
m_backgroundLoaded(other.m_backgroundLoaded), m_spritesLoaded(other.m_spritesLoaded)
{
	m_loadText = std::make_unique<TextBar>(*other.m_loadText);
}

SplashScreenState & SplashScreenState::operator=(const SplashScreenState & other)
{
	GameState::operator=(other);
	m_timer = other.m_timer;
	m_audioLoaded = other.m_audioLoaded;
	m_backgroundLoaded = other.m_backgroundLoaded;
	m_spritesLoaded = other.m_spritesLoaded;
	m_loadText = std::make_unique<TextBar>(*other.m_loadText);
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
		aie::Input* input = aie::Input::getInstance();
		// Load resources
		if (!m_backgroundLoaded) {
			TexturePtr texture = m_app->getResourceManager()->getTexture(filepath::menu_background);
			texture = m_app->getResourceManager()->getTexture(filepath::castle_background);
			texture = m_app->getResourceManager()->getTexture(filepath::win_background);
			m_loadText->setContent(load_sprite_msg);	// Update load message
			m_backgroundLoaded = true;
		} 
		else if (!m_spritesLoaded) {
			m_app->getEntityFactory()->loadResources();
			m_loadText->setContent(load_audio_msg);		// Update load message
			m_spritesLoaded = true;
		}
		else if (!m_audioLoaded) {
			AudioPtr audio = m_app->getResourceManager()->getAudio(filepath::win_music);
			audio = m_app->getResourceManager()->getAudio(filepath::castle_music);
			m_audioLoaded = true;
			m_loadText->setContent(load_done_msg);		// Update load message
		}
		else if (m_timer > splash_duration|| input->getPressedKeys().size() != 0) {
			// Let player skip if everything loaded
			m_shouldTransition = true;
			m_target = GameStateMachine::main_menu;
		}
	}
}

void SplashScreenState::draw(aie::Renderer2D* renderer)
{
	//draw splashscreen image
	renderer->drawSprite(m_splashImage->get(), 640, 360);
	m_loadText->draw(renderer);
}


void SplashScreenState::onEnter()
{
	GameState::onEnter();
	// Play music
	AudioPtr m_music = m_app->getResourceManager()->getAudio(filepath::menu_music);
	m_music->get()->setLooping(true);
	if (!m_music->get()->getIsPlaying()) {
		m_music->get()->play();
	}
	m_splashImage = m_app->getResourceManager()->getTexture(filepath::splash_background);
	m_timer = 0;
	m_audioLoaded = m_backgroundLoaded = m_spritesLoaded = false;
}

void SplashScreenState::onExit()
{
	GameState::onExit();
	// Music continues in MainMenuState, so no need to stop it
}

