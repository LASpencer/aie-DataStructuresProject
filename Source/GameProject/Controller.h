#pragma once
#include "Component.h"

class Controller 
	: public Component {
public:
	Controller();
	virtual ~Controller();

	virtual Identifier getID();
};