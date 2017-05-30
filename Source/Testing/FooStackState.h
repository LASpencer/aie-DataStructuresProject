#pragma once
#include "State.h"

class FooStackState :
	public StackState
{
public:
	FooStackState();
	virtual ~FooStackState();

	virtual FooStackState* clone() const;

	virtual void onEnter();
	virtual void onExit();

	virtual void onFocus();
	virtual void onLoseFocus();

	virtual int getValue();

	virtual void update();

protected:
	int value;
	bool m_focus;
};

class BarStackState :
	public FooStackState
{
public:
	BarStackState();
	virtual ~BarStackState();

	virtual BarStackState* clone() const;

	virtual void onEnter();
	virtual void onExit();

	virtual void update();
};