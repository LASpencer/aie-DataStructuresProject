#include "stdafx.h"
#include "MainMenuState.h"
#include "GameProjectApp.h"
#include "GameStateMachine.h"
#include "Transition.h"
#include "OnClickCondition.h"
#include "InputEvent.h"

const float MainMenuState::play_button_x = 640.0f;
const float MainMenuState::play_button_y = 400.0f;
const float MainMenuState::exit_button_x = 640.0f;
const float MainMenuState::exit_button_y = 200.0f;
const std::string MainMenuState::button_font_path = "./font/consolas_bold.ttf";
const unsigned short MainMenuState::button_font_height = 32;

MainMenuState::MainMenuState(GameProjectApp* app) : GameState(app)
{
	FontPtr buttonFont = m_app->getResourceManager()->getFont(button_font_path, button_font_height);
	m_playButton = std::make_shared<Button>(buttonFont, "Play",play_button_x, play_button_y);
	m_exitButton = std::make_shared<Button>(buttonFont, "Quit",exit_button_x, exit_button_y);
	m_playButton->addObserver(shared_from_this());
	m_exitButton->addObserver(shared_from_this());
}


MainMenuState::~MainMenuState()
{
}

MainMenuState::MainMenuState(const MainMenuState & other) : GameState(other), m_menuImage(other.m_menuImage)
{

}

State * MainMenuState::clone() const
{
	return new MainMenuState(*this);
}

void MainMenuState::update(float deltaTime)
{
	//TODO select menu options
	m_playButton->update(deltaTime);
	m_exitButton->update(deltaTime);
}

void MainMenuState::draw(aie::Renderer2D* renderer)
{
	//TODO draw menu
	renderer->drawSprite(m_menuImage->get(), 640, 360);
	m_playButton->draw(renderer);
	m_exitButton->draw(renderer);
}

void MainMenuState::onEnter()
{
	GameState::onEnter();
	m_menuImage = m_app->getResourceManager() ->getTexture("./textures/mainMenu.png");
}

void MainMenuState::notify(Subject * subject, EventBase * event)
{
	switch (event->getEventID()) {
	case(EventBase::clicked):
		if (m_playButton.get() == subject) {
			m_shouldTransition = true;
			m_target = GameStateMachine::battle_state;
		}
		else if (m_exitButton.get() == subject) {
			m_shouldTransition = true;
			m_target = GameStateMachine::final_state;
		}
		break;
	default:
		break;
	}
}

bool MainMenuState::addSubject(Subject * subject)
{
	return true;
}

void MainMenuState::removeSubject(Subject * subject)
{
}
