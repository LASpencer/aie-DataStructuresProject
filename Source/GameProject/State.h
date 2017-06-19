#pragma once
#include "stdafx.h"
#include "Array.h"
#include "Renderer2d.h"

//TODO comment State
class State {
public:
	State();

	virtual ~State();

	virtual State* clone() const = 0;

	// Called when transitioning to the state
	virtual void onEnter();

	// Called when transitioning from the state
	virtual void onExit();

	virtual void update(float deltaTime) = 0;
	virtual void draw(aie::Renderer2D* renderer) = 0;

	bool shouldTransition();
	int getTarget();

protected:
	bool m_shouldTransition;
	int m_target;
};

class StackState : public State {
public:
	StackState();

	virtual ~StackState();

	// Called when transitioning to the state
	virtual void onEnter();

	// Called when transitioning from the state
	virtual void onExit();

	// Called when state above is popped
	virtual void onFocus();

	// Called when a state is pushed onto this
	virtual void onLoseFocus();

	bool shouldPop();

	bool shouldPush();

protected:
	bool m_focus;
	bool m_shouldPop;
	bool m_shouldPush;
};