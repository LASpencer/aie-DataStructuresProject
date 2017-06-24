#pragma once
#include "Input.h"
#include "GameState.h"
#include "ResourceManager.h"
#include "Component.h"
#include "Observer.h"

class Hero;
/*	This state is used for playing the game. 
	The components for each entity are updated and drawn, until
	the player reaches the door or quits the game.

	PauseState pushed if pause key (Esc) pressed
	Transition to WinState on player collision with door
	*/
class BattleState :
	public GameState, public Observer
{
public:
	static const aie::EInputCodes pause_key;
	static const aie::EInputCodes toggle_hitboxes_key;

	BattleState(GameProjectApp* app);
	virtual ~BattleState();
	BattleState(const BattleState& other);
	BattleState& operator=(const BattleState& other);

	State* clone() const;

	// Update all components and perform collision detection
	virtual void update(float deltaTime);

	// Draw the background and all sprites
	virtual void draw(aie::Renderer2D* renderer);

	// Create all entities in the game
	virtual void onEnter();

	// Remove all entities from the list 
	virtual void onExit();

	virtual void onFocus();

	virtual void onLoseFocus();

	virtual void notify(Subject* subject, EventBase* event) ;

	virtual bool addSubject(Subject* subject);
	virtual void removeSubject(Subject* subject);

protected:
	TexturePtr m_battleImage;		// Background image for game
	AudioPtr	m_music;
	
};

