#include "Transition.h"
#include "Condition.h"

bool Transition::isConditionMet()
{
	return m_condition->test;
}

int Transition::getTargetID() const
{
	return m_targetID;
}
