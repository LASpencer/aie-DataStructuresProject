#include "stdafx.h"
#include "BinaryCondition.h"

BinaryCondition::BinaryCondition() : m_first(), m_second()
{
}

BinaryCondition::BinaryCondition(std::shared_ptr<Condition> first, std::shared_ptr<Condition> second)
	: m_first(first), m_second(second)
{
}

BinaryCondition::~BinaryCondition()
{
}

void BinaryCondition::setFirstCondition(std::shared_ptr<Condition> first)
{
	std::shared_ptr<ComplexCondition> complex = std::dynamic_pointer_cast<ComplexCondition>(first);
	if (complex.get() != nullptr && complex->isDependentOn(this)) {
		throw std::invalid_argument("Cannot set condition holding reference to this");
	}
	m_first = first;
}

void BinaryCondition::setSecondCondition(std::shared_ptr<Condition> second)
{
	std::shared_ptr<ComplexCondition> complex = std::dynamic_pointer_cast<ComplexCondition>(second);
	if (complex.get() != nullptr && complex->isDependentOn(this)) {
		throw std::invalid_argument("Cannot set condition holding reference to this");
	}
	m_second = second;
}

std::shared_ptr<Condition> BinaryCondition::getFirstCondition()
{
	return m_first;
}

std::shared_ptr<Condition> BinaryCondition::getSecondCondition()
{
	return m_second;
}

bool BinaryCondition::isDependentOn(ComplexCondition * condition)
{
	if (condition == this) {
		return true;
	}
	else if (condition == m_first.get() || condition == m_second.get()) {
		// Dependent on conditions
		return true;
	}
	else {
		// If complex first or second, this depends on anything they depend on
		std::shared_ptr<ComplexCondition> complexFirst = std::dynamic_pointer_cast<ComplexCondition>(m_first);
		std::shared_ptr<ComplexCondition> complexSecond = std::dynamic_pointer_cast<ComplexCondition>(m_second);
		bool firstDepends = false;
		bool secondDepends = false;
		if (complexFirst.get() != nullptr) {
			firstDepends = complexFirst->isDependentOn(condition);
		}
		if (complexSecond.get() != nullptr) {
			secondDepends = complexSecond->isDependentOn(condition);
		}
		return firstDepends || secondDepends;
	}
}
