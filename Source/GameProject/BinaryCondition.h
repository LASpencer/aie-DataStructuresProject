#pragma once
#include "ComplexCondition.h"

// Base class for complex conditions implementing binary boolean operations
class BinaryCondition : public ComplexCondition {
public:
	BinaryCondition();
	BinaryCondition(std::shared_ptr<Condition> first, std::shared_ptr<Condition> second);
	virtual ~BinaryCondition();

	void setFirstCondition(std::shared_ptr<Condition> first);
	void setSecondCondition(std::shared_ptr<Condition> second);

	std::shared_ptr<Condition> getFirstCondition();
	std::shared_ptr<Condition> getSecondCondition();

	virtual bool isDependentOn(ComplexCondition* condition);
protected:
	std::shared_ptr<Condition> m_first;
	std::shared_ptr<Condition> m_second;
};