#include "stdafx_test.h"
#include "BarState.h"


BarState::BarState()
{
}


BarState::~BarState()
{
}

State * BarState::clone() const
{
	return new BarState(*this);
}

void BarState::onEnter()
{
	value = 10;
}

void BarState::onExit()
{
	value = 0;
}

void BarState::update()
{
	--value;
}


