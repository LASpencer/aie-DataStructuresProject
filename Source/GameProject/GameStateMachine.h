#pragma once
#include "StateMachine.h"
#include "GameState.h"

class GameStateMachine :
	public StateStackMachine<GameState>
{
public:
	GameStateMachine();
	~GameStateMachine();

	//TODO change when ResourceManager refactored to have all resources
	void loadResources(ResourceManager* resourceManager);

	enum states {
		splash_screen,
		main_menu
	};
};

