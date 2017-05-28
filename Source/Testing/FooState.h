#pragma once
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

