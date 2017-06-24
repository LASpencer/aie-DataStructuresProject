#include "stdafx.h"
#include "WinState.h"
#include "GameProjectApp.h"
#include "Input.h"
#include "Filepaths.h"

const std::string WinState::win_message = "You win!";
const std::string WinState::win_font_path = filepath::consolas_bold_path;
const std::string WinState::button_font_path = filepath::consolas_bold_path;
const unsigned short WinState::win_font_height = 64;
const unsigned short WinState::button_font_height = 32;
const float WinState::text_pos_x = 515.f;
const float WinState::text_pos_y = 650.f;
const float WinState::menu_button_x = 1150.f;
const float WinState::menu_button_y = 200.f;
const float WinState::quit_button_x = 1150.f;
const float WinState::quit_button_y = 100.f;
const float WinState::button_width = 200.f;
const float WinState::button_height = 50.f;


WinState::WinState(GameProjectApp * app) : GameState(app)
{
	FontPtr buttonFont = m_app->getResourceManager()->getFont(button_font_path, button_font_height);
	FontPtr winFont = m_app->getResourceManager()->getFont(win_font_path, win_font_height);
	m_menuButton = std::make_shared<Button>(buttonFont, "Main Menu", menu_button_x, menu_button_y, button_width, button_height);
	m_quitButton = std::make_shared<Button>(buttonFont, "Quit", quit_button_x, quit_button_y, button_width, button_height);
	m_winText = std::make_unique<TextBar>(winFont, win_message, text_pos_x, text_pos_y, 0x000000FF, 0x00000000);
}

WinState::~WinState()
{
}

WinState::WinState(const WinState & other) : GameState(other), m_menuButton(other.m_menuButton), m_quitButton(other.m_quitButton), m_winImage(other.m_winImage)
{
	m_winText = std::make_unique<TextBar>(*(other.m_winText));
}

State * WinState::clone() const
{
	return new WinState(*this);
}

void WinState::update(float deltaTime)
{
	if (m_focus) {
		m_quitButton->update(deltaTime);
		m_menuButton->update(deltaTime);
		if (m_quitButton->isPressed()) {
			m_shouldTransition = true;
			m_target = GameStateMachine::final_state;
		} else if (m_menuButton->isPressed()){
			m_shouldTransition = true;
			m_target = GameStateMachine::main_menu;
		}
	}
}

void WinState::draw(aie::Renderer2D * renderer)
{
	renderer->drawSprite(m_winImage->get(), 515, 360);
	m_winText->draw(renderer);
	m_menuButton->draw(renderer);
	m_quitButton->draw(renderer);
}

void WinState::onEnter()
{
	GameState::onEnter();

	m_music = m_app->getResourceManager()->getAudio(filepath::win_music);
	m_music->get()->setLooping(true);
	if (!m_music->get()->getIsPlaying()) {
		m_music->get()->play();
	}

	m_winImage = m_app->getResourceManager()->getTexture(filepath::win_background);
	m_menuButton->reset();
	m_quitButton->reset();
}

void WinState::onExit()
{
	GameState::onExit();
	m_music->get()->stop();
}
