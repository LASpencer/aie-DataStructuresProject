#pragma once
#include <memory>
#include "Array.h"

class Observer;

class Subject
{
public:
	Subject();
	~Subject();
	//TODO subject adds and removes observers
protected:
	las::Array<std::weak_ptr<Observer>> m_observers;
};

