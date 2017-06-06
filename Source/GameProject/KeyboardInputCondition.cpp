#include "stdafx.h"
#include "KeyboardInputCondition.h"
#include "Input.h"

KeyboardInputCondition::KeyboardInputCondition()
	: m_key(aie::INPUT_KEY_UNKNOWN), m_state(pressed)
{
}

KeyboardInputCondition::KeyboardInputCondition(aie::EInputCodes key, key_state state)
	: m_key(key), m_state(state)
{
}


KeyboardInputCondition::~KeyboardInputCondition()
{
}

void KeyboardInputCondition::setKeyState(key_state state)
{
	m_state = state;
}

void KeyboardInputCondition::setKey(aie::EInputCodes key)
{
	m_key = key;
}

bool KeyboardInputCondition::test()
{
	aie::Input* input = aie::Input::getInstance();
	switch (m_state) {
	case(pressed):
		return input->wasKeyPressed(m_key);
	case(released):
		return input->wasKeyReleased(m_key);
	case(down):
		return input->isKeyDown(m_key);

	}
}
