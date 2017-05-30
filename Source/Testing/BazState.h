#pragma once
#include "FooState.h"
class BazState :
	public FooState
{
public:
	BazState();
	virtual ~BazState();

	virtual BazState* clone() const;

	virtual void onEnter();
	virtual void onExit();

	virtual void update();
};

