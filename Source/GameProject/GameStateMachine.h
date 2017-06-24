#pragma once
#include "StateMachine.h"
#include "GameState.h"

class GameProjectApp;

/*	State Machine defining the game state
*/
class GameStateMachine :
	public StateStackMachine<GameState>
{
public:
	GameStateMachine(GameProjectApp* app);
	~GameStateMachine();

	enum states {
		splash_screen,
		main_menu,
		battle_state,
		pause_state,
		win_state,
		final_state
	};

protected:
	GameProjectApp* m_app;
};

