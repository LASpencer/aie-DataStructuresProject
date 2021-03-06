#include "stdafx.h"
#include "WinState.h"
#include "GameProjectApp.h"
#include "Input.h"
#include "InputEvent.h"
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
const float WinState::music_volume = 0.4f;


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

void WinState::update(float deltaTime)
{
	if (m_focus) {
		m_quitButton->update(deltaTime);
		m_menuButton->update(deltaTime);
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
	// Play victory music
	m_music = m_app->getResourceManager()->getAudio(filepath::win_music);
	m_music->get()->setLooping(true);
	m_music->get()->setGain(music_volume);	// Full volume is too loud
	if (!m_music->get()->getIsPlaying()) {
		m_music->get()->play();
	}

	m_winImage = m_app->getResourceManager()->getTexture(filepath::win_background);
	// Reset and observe buttons
	m_menuButton->reset();
	m_menuButton->addObserver(shared_from_this());
	m_quitButton->reset();
	m_quitButton->addObserver(shared_from_this());
}

void WinState::onExit()
{
	GameState::onExit();
	m_music->get()->stop();
}

void WinState::notify(Subject * subject, EventBase * event)
{
	// If button clicked, transition to indicated state
	if (event->getEventID() == EventBase::clicked) {
		InputEvent* click = dynamic_cast<InputEvent*>(event);
		assert(click != nullptr);
		if (click->getInputCode() == aie::INPUT_MOUSE_BUTTON_LEFT) {
			if (subject == m_menuButton.get()) {
				m_shouldTransition = true;
				m_target = GameStateMachine::main_menu;
			}
			else if (subject == m_quitButton.get()) {
				m_shouldTransition = true;
				m_target = GameStateMachine::final_state;
			}
		}
	}
}

bool WinState::addSubject(Subject * subject)
{
	return true;
}

void WinState::removeSubject(Subject * subject)
{
}
