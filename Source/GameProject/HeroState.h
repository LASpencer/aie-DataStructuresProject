#pragma once
#include "State.h"
#include "Input.h"
#include "Observer.h"

class Entity;
typedef std::shared_ptr<Entity> EntityPtr;
typedef std::weak_ptr<Entity>	EntityWeakPtr;

class HeroState;
typedef std::shared_ptr<HeroState> HeroStatePtr;

class HeroController;

//TODO write and implement
//TODO write HeroStateMachine
class HeroState 
	: public State, public Observer
{
public:
	HeroState(HeroController* controller);
	virtual ~HeroState();

	void setHero(EntityPtr hero);

	virtual void onEnter();

	virtual void onExit();

	virtual bool addSubject(Subject* subject);
	virtual void removeSubject(Subject* subject);

	static const aie::EInputCodes left_move_button;
	static const aie::EInputCodes right_move_button;
	static const aie::EInputCodes jump_button;
	static const aie::EInputCodes crouch_button;
	static const aie::EInputCodes attack_button;

protected:
	EntityWeakPtr m_hero;
	HeroController* m_controller;
};