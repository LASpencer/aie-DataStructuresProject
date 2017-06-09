#pragma once
#include "EventBase.h"

// Event requiring no additional information
class Event : public EventBase {
public:
	Event(event_id id);
	virtual ~Event();
protected:
	virtual bool isValidID(event_id id);
};