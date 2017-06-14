#include "stdafx.h"
#include "KeyboardInputCondition.h"
#include "Input.h"
#include "InputEvent.h"

KeyboardInputCondition::KeyboardInputCondition()
	: m_key(aie::INPUT_KEY_UNKNOWN), m_states({ {pressed, true} }), m_triggered(false), m_subscribed(false)
{
}

KeyboardInputCondition::KeyboardInputCondition(aie::EInputCodes key, key_state state)
	: m_key(key), m_states({ {state,true } }), m_triggered(false), m_subscribed(false)
{
}


KeyboardInputCondition::~KeyboardInputCondition()
{
}

void KeyboardInputCondition::addKeyState(key_state state)
{
	m_states[state] = true;
}

void KeyboardInputCondition::removeKeyState(key_state state)
{
	m_states[state] = false;
}


void KeyboardInputCondition::setKey(aie::EInputCodes key)
{
	m_key = key;
}

bool KeyboardInputCondition::test()
{
	return m_triggered;
}

void KeyboardInputCondition::notify(Subject * subject, EventBase * event)
{
	InputEvent* inputEvent = dynamic_cast<InputEvent*>(event);
	switch(event->getEventID()) {
	case(EventBase::event_id::frame_start):
		m_triggered = false;
	}
}

bool KeyboardInputCondition::addSubject(Subject * subject)
{
	if (m_subscribed) {
		return false;
	} else {
		m_subscribed = true;
		return true;
	}
}

void KeyboardInputCondition::removeSubject(Subject * subject)
{
	m_subscribed = false;
}
