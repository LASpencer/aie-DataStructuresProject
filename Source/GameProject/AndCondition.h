#pragma once
#include "BinaryCondition.h"

//TODO test And condition
class AndCondition : public BinaryCondition {
public:
	AndCondition();
	AndCondition(std::shared_ptr<Condition> first, std::shared_ptr<Condition> second);
	virtual ~AndCondition();

	virtual bool test();


};