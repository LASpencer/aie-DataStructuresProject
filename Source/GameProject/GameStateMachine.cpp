#include "stdafx.h"
#include "GameStateMachine.h"
#include "GameState.h"
#include "SplashScreenState.h"
#include "MainMenuState.h"
#include "TimerCondition.h"

GameStateMachine::GameStateMachine()
{
	std::shared_ptr<SplashScreenState> splashScreen = std::make_shared<SplashScreenState>();
	std::shared_ptr<TimerCondition> splashEndTimer = std::make_shared<TimerCondition>();
	splashScreen->addObserver(splashEndTimer);
	splashScreen->addTransition(std::make_shared<Transition>(splashEndTimer, GameStateMachine::states::main_menu));
	addState(splash_screen, splashScreen);

	std::shared_ptr<MainMenuState> mainMenu = std::make_shared<MainMenuState>();
	addState(main_menu, mainMenu);
}


GameStateMachine::~GameStateMachine()
{
}

void GameStateMachine::loadResources(ResourceManager* resourceManager)
{
	for (std::pair<int,std::shared_ptr<GameState>> state : m_states) {
		state.second->loadResources(resourceManager);
	}
}
