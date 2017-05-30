#include "stdafx_test.h"
#include "FooStackState.h"
#include "State.h"


FooStackState::FooStackState() :m_focus(false)
{
}


FooStackState::~FooStackState()
{
}

FooStackState * FooStackState::clone() const
{
	return new FooStackState(*this);
}

void FooStackState::onEnter()
{
	value = 1;
	m_focus = true;
}

void FooStackState::onExit()
{
	value = 0;
}

void FooStackState::onFocus()
{
	m_focus = true;
}

void FooStackState::onLoseFocus()
{
	m_focus = false;
}

int FooStackState::getValue()
{
	return value;
}

void FooStackState::update()
{
	++value;
	if (m_focus) {
		value += 10;
	}
}

BarStackState::BarStackState() : FooStackState()
{
}

BarStackState::~BarStackState()
{
}

BarStackState * BarStackState::clone() const
{
	return new BarStackState(*this);
}

void BarStackState::onEnter()
{
	value = 100;
	m_focus = true;
}

void BarStackState::onExit()
{
	value = 0;
}

void BarStackState::update()
{
	++value;
	if (m_focus) {
		value -= 10;
	}
}
