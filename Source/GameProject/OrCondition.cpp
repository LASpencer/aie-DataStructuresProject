#include "stdafx.h"
#include "OrCondition.h"

OrCondition::OrCondition() : BinaryCondition()
{
}

OrCondition::OrCondition(std::shared_ptr<Condition> first, std::shared_ptr<Condition> second)
	: BinaryCondition(first, second)
{
}

OrCondition::~OrCondition()
{
}

bool OrCondition::test()
{
	return (m_first && m_first->test()) || (m_second && m_second->test());
}
