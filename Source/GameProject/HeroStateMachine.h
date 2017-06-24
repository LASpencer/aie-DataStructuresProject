#pragma once
#include "stdafx.h"
#include "StateMachine.h"
#include "HeroState.h"

class HeroController;

class Entity;
typedef std::shared_ptr<Entity> EntityPtr;
typedef std::weak_ptr<Entity>	EntityWeakPtr;

// State machine for controlling the hero
class HeroStateMachine :
	public StateMachine<HeroState>
{
public:
	HeroStateMachine(HeroController* controller);
	~HeroStateMachine();

	/** Sets entity controlled by this state machine
	*	@param hero Entity with sprite and collider components, tagged as player*/
	void setHero(EntityPtr hero);

	enum states {
		idle_state,
		walk_state,
		crouch_state,
		fall_state,
		jump_state
	};

protected:
	EntityWeakPtr m_hero;
	HeroController* m_controller;
};