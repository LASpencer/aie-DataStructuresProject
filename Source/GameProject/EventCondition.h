#pragma once
#include "Condition.h"
#include "Observer.h"

class EventCondition :
	public Condition, public Observer
{
public:
	EventCondition();
	virtual ~EventCondition();

	virtual EventCondition* clone() const = 0;
};

