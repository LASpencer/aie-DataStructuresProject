#include "stdafx.h"
#include "NotCondition.h"

NotCondition::NotCondition() : m_condition()
{
}

NotCondition::NotCondition(std::shared_ptr<Condition> condition) : m_condition(condition)
{
}

NotCondition::~NotCondition()
{
}

void NotCondition::setCondition(std::shared_ptr<Condition> condition)
{
	//Try cast condition to complex condition, and ask if it's dependent on this
	std::shared_ptr<ComplexCondition> complex = std::dynamic_pointer_cast<ComplexCondition>(condition);
	if (complex.get() != nullptr && complex->isDependentOn(this)) {
		throw std::invalid_argument("Cannot set condition holding reference to this");
	}
	m_condition = condition;
}

std::shared_ptr<Condition> NotCondition::getCondition()
{
	return m_condition;
}

bool NotCondition::isDependentOn(ComplexCondition* condition)
{
	if (condition == this) {
		// Always dependent on self
		return true;
	}
	else if (condition == m_condition.get()) {
		// Dependent on m_condition
		return true;
	}
	else {
		// If m_condition is complex, this depends on anything m_condition depends upon
		std::shared_ptr<ComplexCondition> complex = std::dynamic_pointer_cast<ComplexCondition>(m_condition);
		if (complex.get() != nullptr) {
			return complex->isDependentOn(condition);
		} else {
			return false;
		}
	}
}

bool NotCondition::test()
{
	return !m_condition->test();
}
