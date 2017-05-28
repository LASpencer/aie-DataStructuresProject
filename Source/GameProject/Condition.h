#pragma once

//TODO comment condition
class Condition
{
public:
	Condition();
	virtual ~Condition();

	virtual bool test() = 0;
};

