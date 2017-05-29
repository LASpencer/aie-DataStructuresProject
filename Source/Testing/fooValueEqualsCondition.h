#pragma once
#include "Condition.h"
#include "FooState.h"
#include "StateMachine.h"


class fooValueEqualsCondition :
	public Condition
{
public:
	fooValueEqualsCondition();

	fooValueEqualsCondition(int value, std::shared_ptr<FooState> state);

	~fooValueEqualsCondition();

	bool test();

	void setValue(int value);

	void setState(std::shared_ptr<FooState> state);

protected:
	int m_value;
	std::weak_ptr<FooState> m_state;
};

class fooDivisibleByCondition :
	public Condition {
public:
	fooDivisibleByCondition();

	fooDivisibleByCondition(int value, StateMachine<FooState>* machine);

	~fooDivisibleByCondition();

	bool test();

	void setValue(int value);

	void setMachine(StateMachine<FooState>* machine);

protected:
	int m_value;
	StateMachine<FooState>* m_machine;
};