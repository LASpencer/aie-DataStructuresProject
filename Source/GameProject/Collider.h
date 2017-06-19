#pragma once
#include "Component.h"
#include "Subject.h"
#include "EventManager.h"
class Collider :
	public Component, public Subject
{
public:
	Collider();
	~Collider();

	

protected:
	EventManager m_eventManager;
	
};

