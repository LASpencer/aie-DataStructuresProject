#include "stdafx.h"
#include "GameStateMachine.h"
#include "GameState.h"
#include "SplashScreenState.h"
#include "MainMenuState.h"
#include "FinalState.h"
#include "BattleState.h"
#include "WinState.h"
#include "PauseState.h"


GameStateMachine::GameStateMachine(GameProjectApp* app)
{
	m_app = app;

	std::shared_ptr<SplashScreenState> splashScreen = std::make_shared<SplashScreenState>(app);
	addState(splash_screen, splashScreen);

	std::shared_ptr<MainMenuState> mainMenu = std::make_shared<MainMenuState>(app);
	addState(main_menu, mainMenu);

	std::shared_ptr<BattleState> battle = std::make_shared<BattleState>(app);
	addState(battle_state, battle);

	std::shared_ptr<PauseState> pause = std::make_shared<PauseState>(app);
	addState(pause_state, pause);

	std::shared_ptr<WinState> win = std::make_shared<WinState>(app);
	addState(win_state, win);

	std::shared_ptr<FinalState> finalState = std::make_shared<FinalState>(app);
	addState(final_state, finalState);
}


GameStateMachine::~GameStateMachine()
{
}
