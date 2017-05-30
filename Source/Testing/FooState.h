#pragma once
#include "stdafx_test.h"
#include "State.h"

class FooState :
	public State
{
public:
	FooState();
	virtual ~FooState();

	virtual FooState* clone() const;

	virtual void onEnter();
	virtual void onExit();

	virtual int getValue();

	virtual void update();

protected:
	int value;
};

