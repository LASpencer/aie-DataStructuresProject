#include "stdafx.h"
#include "State.h"
#include "Condition.h"
#include "Transition.h"

State::State()
{
}

State::~State()
{
}

bool State::shouldTransition()
{
	return m_shouldTransition;
}

int State::getTarget()
{
	return m_target;
}



StackState::StackState() {

}

StackState::~StackState()
{
}

bool StackState::shouldPop()
{
	return m_shouldPop;
}

bool StackState::shouldPush()
{
	return m_shouldPush;
}