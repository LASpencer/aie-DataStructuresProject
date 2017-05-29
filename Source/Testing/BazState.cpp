#include "stdafx_test.h"
#include "BazState.h"


BazState::BazState()
{
}


BazState::~BazState()
{
}

void BazState::onEnter()
{
	value = 50;
}

void BazState::onExit()
{
	value = 0;
}

void BazState::update()
{
	++value;
}
