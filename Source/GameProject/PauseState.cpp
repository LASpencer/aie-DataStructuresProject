#include "stdafx.h"
#include "PauseState.h"
#include "TextBar.h"
#include "GameProjectApp.h"
#include "Event.h"
#include "Input.h"
#include "InputEvent.h"
#include "Filepaths.h"

const std::string PauseState::pause_message = "Paused";
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
	FontPtr pauseFont = m_app->getResourceManager()->getFont(filepath::consolas_bold_path, pause_font_height);
	FontPtr buttonFont = m_app->getResourceManager()->getFont(filepath::consolas_bold_path, button_font_height);
	m_quitButton = std::make_shared<Button>(buttonFont, "Quit", quit_button_x, quit_button_y, button_width, button_height);
	m_pauseText = std::make_unique<TextBar>(pauseFont, pause_message, text_pos_x, text_pos_y, TextBar::def_text_colour, 0x00000000);
}


PauseState::~PauseState()
{
}

PauseState::PauseState(const PauseState & other) : GameState(other), m_quitButton(other.m_quitButton)
{
	m_pauseText = std::make_unique<TextBar>(*other.m_pauseText);
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

	if (m_focus) {
		m_quitButton->update(deltaTime);
	if(aie::Input::getInstance()->wasKeyPressed(unpause_key)){
			// Unpause on key press
			m_shouldPop = true;
		}
	}
}

void PauseState::draw(aie::Renderer2D * renderer)
{
	// Grey out screen
	renderer->setRenderColour(0x00000040);
	renderer->drawBox(640, 360, 1280, 720);
	// Draw pause screen elements
	m_pauseText->draw(renderer);
	m_quitButton->draw(renderer);
	renderer->setRenderColour(0xffffffff);
}

void PauseState::onEnter()
{
	GameState::onEnter();
	m_quitButton->reset();
	m_quitButton->addObserver(shared_from_this());
}

void PauseState::notify(Subject * subject, EventBase * event)
{
	// If quit button clicked, transition to final state
	if (event->getEventID() == EventBase::clicked) {
		InputEvent* click = dynamic_cast<InputEvent*>(event);
		assert(click != nullptr);
		if (click->getInputCode() == aie::INPUT_MOUSE_BUTTON_LEFT) {
			if (subject == m_quitButton.get()) {
				m_shouldTransition = true;
				m_target = GameStateMachine::final_state;
			}
		}
	}
}

bool PauseState::addSubject(Subject * subject)
{
	return true;
}

void PauseState::removeSubject(Subject * subject)
{
}
