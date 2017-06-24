#include "stdafx.h"
#include "MainMenuState.h"
#include "GameProjectApp.h"
#include "GameStateMachine.h"
#include "InputEvent.h"
#include "Filepaths.h"

const std::string MainMenuState::title_message = "Dark Castle";
const float MainMenuState::button_width = 200.0f;
const float MainMenuState::button_height = 50.0f;
const float MainMenuState::play_button_x = 1150.0f;
const float MainMenuState::play_button_y = 200.0f;
const float MainMenuState::exit_button_x = 1150.0f;
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
	return *this;
}

State * MainMenuState::clone() const
{
	return new MainMenuState(*this);
}

void MainMenuState::update(float deltaTime)
{
	if (m_focus) {
		// Update animation frames
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
		// Check for button clicks
		/*if (m_playButton->isPressed()) {
			m_shouldTransition = true;
			m_target = GameStateMachine::battle_state;
		}
		else if (m_exitButton->isPressed()) {
			m_shouldTransition = true;
			m_target = GameStateMachine::final_state;
		}*/
	}
}

void MainMenuState::draw(aie::Renderer2D* renderer)
{
	// Draw animated background
	renderer->setUVRect(m_uvCol * 0.25f, m_uvRow*0.25f, 0.25f, 0.25f);
	renderer->drawSprite(m_menuImage->get(), 640, 360, 720, 720);
	// Draw menu elements
	m_titleText->draw(renderer);
	m_playButton->draw(renderer);
	m_exitButton->draw(renderer);
}

void MainMenuState::onEnter()
{
	GameState::onEnter();
	// Play music
	m_music = m_app->getResourceManager()->getAudio(filepath::menu_music);
	m_music->get()->setLooping(true);
	if (!m_music->get()->getIsPlaying()) {
		m_music->get()->play();
	}
	m_menuImage = m_app->getResourceManager()->getTexture(filepath::menu_background);
	// Reset animation to first frame
	m_uvCol = m_uvRow = 0;
	m_timer = 0.f;
	m_playButton->reset();
	m_playButton->addObserver(shared_from_this());
	m_exitButton->reset();
	m_exitButton->addObserver(shared_from_this());
}

void MainMenuState::onExit()
{
	GameState::onExit();
	//Stop music
	m_music->get()->stop();
}

void MainMenuState::notify(Subject * subject, EventBase * event)
{
	if (event->getEventID() == EventBase::clicked) {
		InputEvent* click = dynamic_cast<InputEvent*>(event);
		assert(click != nullptr);
		if (click->getInputCode() == aie::INPUT_MOUSE_BUTTON_LEFT) {
			if (subject == m_playButton.get()) {
				m_shouldTransition = true;
				m_target = GameStateMachine::battle_state;
			}
			else if (subject == m_exitButton.get()) {
				m_shouldTransition = true;
				m_target = GameStateMachine::final_state;
			}
		}
	}
}

bool MainMenuState::addSubject(Subject * subject)
{
	return true;
}

void MainMenuState::removeSubject(Subject * subject)
{
}
