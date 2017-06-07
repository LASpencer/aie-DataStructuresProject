#pragma once
#include "BinaryCondition.h"

//TODO test Or condition
class OrCondition : public BinaryCondition {
public:
	OrCondition();
	OrCondition(std::shared_ptr<Condition> first, std::shared_ptr<Condition> second);
	virtual ~OrCondition();


	virtual bool test();

protected:
	std::shared_ptr<Condition> m_first;
	std::shared_ptr<Condition> m_second;
};