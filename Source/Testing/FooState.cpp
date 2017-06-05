#include "stdafx_test.h"
#include "FooState.h"



FooState::FooState()
{
}


FooState::~FooState()
{
}

State * FooState::clone() const
{
	return new FooState(*this);
}

void FooState::onEnter()
{
	value = 1;
}

void FooState::onExit()
{
	value = 0;
}

int FooState::getValue()
{
	return value;
}

void FooState::update()
{
	++value;
}
