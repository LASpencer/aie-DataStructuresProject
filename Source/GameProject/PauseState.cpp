#include "stdafx.h"
#include "PauseState.h"
#include "TextBar.h"
#include "GameProjectApp.h"
#include "Event.h"
#include "Filepaths.h"

const std::string PauseState::pause_message = "Paused";
const std::string PauseState::pause_font_path = filepath::consolas_bold_path;
const std::string PauseState::button_font_path = filepath::consolas_bold_path;
const unsigned short PauseState::pause_font_height = 64;
const unsigned short PauseState::button_font_height = 32;
const float PauseState::text_pos_x = 640;
const float PauseState::text_pos_y = 500;
const float PauseState::quit_button_x = 640;
const float PauseState::quit_button_y = 300;
const float PauseState::button_width = 200.0f;
const float PauseState::button_height = 50.0f;

const aie::EInputCodes PauseState::unpause_key = aie::INPUT_KEY_ESCAPE;

PauseState::PauseState(GameProjectApp* app) : GameState(app)
{
	FontPtr pauseFont = m_app->getResourceManager()->getFont(pause_font_path, pause_font_height);
	FontPtr buttonFont = m_app->getResourceManager()->getFont(button_font_path, button_font_height);
	m_quitButton = std::make_shared<Button>(buttonFont, "Quit", quit_button_x, quit_button_y, button_width, button_height);
	m_pauseText = std::make_unique<TextBar>(pauseFont, pause_message, text_pos_x, text_pos_y, TextBar::def_text_colour, 0x00000000);
	//TODO follow quit button
}


PauseState::~PauseState()
{
}

PauseState::PauseState(const PauseState & other) : GameState(other), m_quitButton(other.m_quitButton)
{
	m_pauseText = std::make_unique<TextBar>(*other.m_pauseText);
	//TODO follow quit button
}

PauseState & PauseState::operator=(const PauseState & other)
{
	GameState::operator=(other);
	m_quitButton = other.m_quitButton;
	m_pauseText = std::make_unique<TextBar>(*other.m_pauseText);
	return *this;
}

State * PauseState::clone() const
{
	return new PauseState(*this);
}

void PauseState::update(float deltaTime)
{
	//TODO pop if esc pressed
	//TODO transition to final_state if quit button pressed
	if (m_focus) {
		m_quitButton->update(deltaTime);
		if (m_quitButton->isPressed()) {
			m_shouldTransition = true;
			m_target = GameStateMachine::final_state;
		} else if(aie::Input::getInstance()->wasKeyPressed(unpause_key)){
			m_shouldPop = true;
		}
	}
}

void PauseState::draw(aie::Renderer2D * renderer)
{
	// Grey out screen
	renderer->setRenderColour(0x00000040);
	renderer->drawBox(640, 360, 1280, 720);
	m_pauseText->draw(renderer);
	m_quitButton->draw(renderer);
	renderer->setRenderColour(0xffffffff);
}

void PauseState::onEnter()
{
	GameState::onEnter();
	m_quitButton->reset();
}
