#include "stdafx.h"
#include "MainMenuState.h"
#include "GameProjectApp.h"
#include "GameStateMachine.h"
#include "Transition.h"
#include "OnClickCondition.h"

const float MainMenuState::play_button_x = 640.0f;
const float MainMenuState::play_button_y = 400.0f;
const float MainMenuState::exit_button_x = 640.0f;
const float MainMenuState::exit_button_y = 200.0f;

MainMenuState::MainMenuState(GameProjectApp* app) : GameState(app)
{
	m_playButton = std::make_shared<Button>(play_button_x, play_button_y);
	m_exitButton = std::make_shared<Button>(exit_button_x, exit_button_y);
	
	std::shared_ptr<OnClickCondition> clickPlay = std::make_shared<OnClickCondition>();
	addTransition(std::make_shared<Transition>(clickPlay, GameStateMachine::battle_state));
	m_playButton->addObserver(clickPlay);
	std::shared_ptr<OnClickCondition> clickExit = std::make_shared<OnClickCondition>();
	addTransition(std::make_shared<Transition>(clickExit, GameStateMachine::final_state));
	m_exitButton->addObserver(clickExit);
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
