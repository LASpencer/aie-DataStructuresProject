#pragma once
#include "EventCondition.h"
#include "Input.h"
#include "Map.h"

/** A condition that checks keyboard input. Test returns true based on the state of specified key*/
//TODO: MAke it an EventCondition, getting a KeyInputEvent from a specific subject
class KeyboardInputCondition :
	public EventCondition
{
public:
	
	enum key_state {
		pressed,	//Key pressed this frame
		released,	//Key released this frame
		down,		//Key held down
		up	//Key not held down
	};

	KeyboardInputCondition();
	/** @param key key to be checked
	* @param state state in which key must be for test to return true*/
	KeyboardInputCondition(aie::EInputCodes key, key_state state = pressed);
	~KeyboardInputCondition();

	void addKeyState(key_state state);
	void removeKeyState(key_state state);
	void setKey(aie::EInputCodes key);

	// Returns true if specified key is in chosen state
	virtual bool test();

	void notify(Subject* subject, EventBase* event);

	virtual bool addSubject(Subject* subject);
	virtual void removeSubject(Subject* subject);

protected:
	las::Map<key_state, bool> m_states;			// State of key for which test returns true
	aie::EInputCodes m_key;						// Key to check
	bool m_triggered;
	bool m_subscribed;
};

