#include "stdafx.h"
#include "AndCondition.h"

AndCondition::AndCondition() : BinaryCondition()
{
}

AndCondition::AndCondition(std::shared_ptr<Condition> first, std::shared_ptr<Condition> second) : BinaryCondition(first, second)
{
}

AndCondition::~AndCondition()
{
}



bool AndCondition::test()
{
	return m_first && m_second && m_first->test() && m_second->test();
}
