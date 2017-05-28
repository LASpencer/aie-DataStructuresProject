#pragma once
#include "stdafx_test.h"
#include "State.h"

class FooState :
	public State
{
public:
	FooState();
	~FooState();

	virtual void onEnter();
	virtual void onExit();
};

