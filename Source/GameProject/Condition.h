#pragma once
#include "stdafx.h"

//TODO comment condition
class Condition
{
public:
	Condition();
	virtual ~Condition();

	virtual bool test() = 0;
};

