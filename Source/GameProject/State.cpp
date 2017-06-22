#include "stdafx.h"
#include "State.h"


State::State()
{
}

State::~State()
{
}

void State::onEnter()
{
	m_shouldTransition = false;
}

void State::onExit()
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



StackState::StackState() :m_focus(false)
{

}

StackState::~StackState()
{
}

void StackState::onEnter()
{
	State::onEnter();
	m_focus = true;
	m_shouldPop = false;
	m_shouldPush = false;
}

void StackState::onExit()
{
	State::onExit();
}

void StackState::onFocus()
{
	m_focus = true;
	m_shouldTransition = false;
	m_shouldPop = false;
	m_shouldPush = false;
}

void StackState::onLoseFocus()
{
	m_focus = false;
}

bool StackState::shouldPop()
{
	return m_shouldPop;
}

bool StackState::shouldPush()
{
	return m_shouldPush;
}