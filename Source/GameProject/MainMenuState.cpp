#include "stdafx.h"
#include "MainMenuState.h"
#include "GameProjectApp.h"
#include "GameStateMachine.h"
#include "InputEvent.h"
#include "Filepaths.h"

const std::string MainMenuState::title_message = "Dark Castle";
const float MainMenuState::button_width = 200.0f;
const float MainMenuState::button_height = 50.0f;
const float MainMenuState::play_button_x = 1120.0f;
const float MainMenuState::play_button_y = 200.0f;
const float MainMenuState::exit_button_x = 1120.0f;
const float MainMenuState::exit_button_y = 100.0f;
const float MainMenuState::title_pos_x = 640.f;
const float MainMenuState::title_pos_y = 680.f;
const unsigned short MainMenuState::button_font_height = 32;
const unsigned short MainMenuState::title_font_height = 64;

MainMenuState::MainMenuState(GameProjectApp* app) : GameState(app), m_uvCol(0), m_uvRow(0), m_timer(0.f)
{
	FontPtr buttonFont = m_app->getResourceManager()->getFont(filepath::consolas_bold_path, button_font_height);
	FontPtr titleFont = m_app->getResourceManager()->getFont(filepath::consolas_bold_path, title_font_height);
	m_titleText = std::make_unique<TextBar>(titleFont, title_message, title_pos_x, title_pos_y, 0x802020FF, 0x00000000);
	m_playButton = std::make_shared<Button>(buttonFont, "Play",play_button_x, play_button_y, button_width,button_height);
	m_exitButton = std::make_shared<Button>(buttonFont, "Quit",exit_button_x, exit_button_y, button_width, button_height);
}


MainMenuState::~MainMenuState()
{
}

MainMenuState::MainMenuState(const MainMenuState & other) : GameState(other), m_menuImage(other.m_menuImage), m_playButton(other.m_playButton), m_exitButton(other.m_exitButton), m_uvCol(other.m_uvCol), m_uvRow(other.m_uvRow), m_timer(other.m_timer)
{
	m_titleText = std::make_unique<TextBar>(*other.m_titleText);
}

MainMenuState & MainMenuState::operator=(const MainMenuState & other)
{
	GameState::operator=(other);
	m_menuImage = other.m_menuImage;
	m_playButton = other.m_playButton;
	m_exitButton = other.m_exitButton;
	m_uvCol = other.m_uvCol;
	m_uvRow = other.m_uvRow;
	m_timer = other.m_timer;
	m_titleText = std::make_unique<TextBar>(*other.m_titleText);
	//TODO follow play and exit buttons
	return *this;
}

State * MainMenuState::clone() const
{
	return new MainMenuState(*this);
}

void MainMenuState::update(float deltaTime)
{
	if (m_focus) {
		//TODO additional menu options
		m_timer += deltaTime;
		while (m_timer > 0.1f) {
			m_timer -= 0.1f;
			++m_uvCol;
			if (m_uvCol > 3) {
				m_uvCol = 0;
				++m_uvRow;
				if (m_uvRow > 3) {
					m_uvRow = 0;
				}
			}
		}
		m_playButton->update(deltaTime);
		m_exitButton->update(deltaTime);
		if (m_playButton->isPressed()) {
			m_shouldTransition = true;
			m_target = GameStateMachine::battle_state;
		}
		else if (m_exitButton->isPressed()) {
			m_shouldTransition = true;
			m_target = GameStateMachine::final_state;
		}
	}
}

void MainMenuState::draw(aie::Renderer2D* renderer)
{
	//TODO draw menu
	renderer->setUVRect(m_uvCol * 0.25f, m_uvRow*0.25f, 0.25f, 0.25f);
	renderer->drawSprite(m_menuImage->get(), 640, 360, 720, 720);
	m_titleText->draw(renderer);
	m_playButton->draw(renderer);
	m_exitButton->draw(renderer);
}

void MainMenuState::onEnter()
{
	GameState::onEnter();
	m_menuImage = m_app->getResourceManager()->getTexture(filepath::menu_background);
	m_uvCol = m_uvRow = 0;
	m_timer = 0.f;
	m_playButton->reset();
	m_exitButton->reset();
}
