#pragma once
#include <memory>

class Condition;

//TODO comment transition
class Transition {
public:
	Transition(std::shared_ptr<Condition> condition, int targetID) : 
		m_condition(condition), m_targetID(targetID)
	{}

	bool isConditionMet();

	int getTargetID() const;

private:
	std::shared_ptr<Condition> m_condition;
	int m_targetID;
};