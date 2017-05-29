#include "stdafx_test.h"
#include "fooValueEqualsCondition.h"
#include "FooState.h"


fooValueEqualsCondition::fooValueEqualsCondition()
{
}

fooValueEqualsCondition::fooValueEqualsCondition(int value, std::shared_ptr<FooState> state) : m_value(value), m_state(state)
{
}


fooValueEqualsCondition::~fooValueEqualsCondition()
{
}

bool fooValueEqualsCondition::test()
{
	std::shared_ptr<FooState> state(m_state);
	if (state && state->getValue() == m_value) {
		return true;
	} else {
		return false;
	}
}

void fooValueEqualsCondition::setValue(int value)
{
	m_value = value;
}

void fooValueEqualsCondition::setState(std::shared_ptr<FooState> state) 
{
	m_state = state;
}

fooDivisibleByCondition::fooDivisibleByCondition()
{
}

fooDivisibleByCondition::fooDivisibleByCondition(int value, std::shared_ptr<FooState> state) : m_value(value),m_state(state)
{
}

fooDivisibleByCondition::~fooDivisibleByCondition()
{
}

bool fooDivisibleByCondition::test()
{
	std::shared_ptr<FooState> state(m_state);
	if (state) {
		return state->getValue() % m_value == 0;
	}
	else {
		return false;
	}
}

void fooDivisibleByCondition::setValue(int value)
{
	m_value = value;
}

void fooDivisibleByCondition::setState(std::shared_ptr<FooState> state)
{
	m_state = state;
}
