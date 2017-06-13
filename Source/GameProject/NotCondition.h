#pragma once
#include "ComplexCondition.h"

//TODO test, document
class NotCondition : public ComplexCondition {
public:
	NotCondition();
	NotCondition(std::shared_ptr<Condition> condition);
	virtual ~NotCondition();
	
	// 
	void setCondition(std::shared_ptr<Condition> condition);

	std::shared_ptr<Condition> getCondition();


	//Returns true if test depends on conditions test
	virtual bool isDependentOn(ComplexCondition* condition);

	virtual bool test();

protected:
	std::shared_ptr<Condition> m_condition;
};