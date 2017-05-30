#pragma once
#include "FooState.h"
class BarState :
	public FooState
{
public:
	BarState();
	virtual ~BarState();

	virtual BarState* clone() const;

	virtual void onEnter();
	virtual void onExit();

	virtual void update();
};

