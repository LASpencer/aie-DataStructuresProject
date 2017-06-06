#pragma once
#include "Condition.h"
#include "Input.h"

/** A condition that checks keyboard input. Test returns true based on the state of specified key*/
class KeyboardInputCondition :
	public Condition
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

	void setKeyState(key_state state);
	void setKey(aie::EInputCodes key);

	// Returns true if specified key is in chosen state
	virtual bool test();

protected:
	key_state m_state;			// State of key for which test returns true
	aie::EInputCodes m_key;		// Key to check
};

