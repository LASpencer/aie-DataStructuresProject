#include "stdafx.h"
#include "GameStateMachine.h"
#include "GameState.h"
#include "SplashScreenState.h"
#include "MainMenuState.h"
#include "FinalState.h"
#include "BattleState.h"
#include "WinState.h"
#include "PauseState.h"


GameStateMachine::GameStateMachine(GameProjectApp* app) : m_app(app)
{
	// Register states
	addState(splash_screen, std::make_shared<SplashScreenState>(app));
	addState(main_menu, std::make_shared<MainMenuState>(app));
	addState(battle_state, std::make_shared<BattleState>(app));
	addState(pause_state, std::make_shared<PauseState>(app));
	addState(win_state, std::make_shared<WinState>(app));
	addState(final_state, std::make_shared<FinalState>(app));
}


GameStateMachine::~GameStateMachine()
{
}
