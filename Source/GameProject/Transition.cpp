#include "stdafx.h"
#include "Transition.h"
#include "Condition.h"

bool Transition::isConditionMet()
{
	return m_condition->test();
}

std::shared_ptr<const Condition> Transition::getCondition()
{
	return m_condition;
}

int Transition::getTargetID() const
{
	return m_targetID;
}
