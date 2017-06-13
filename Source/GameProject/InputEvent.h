#pragma once
#include "Input.h"
#include "EventBase.h"

class InputEvent : public EventBase {
public:
	InputEvent(event_id id, aie::EInputCodes inputCode);
	virtual ~InputEvent();

	aie::EInputCodes getInputCode();


protected:
	aie::EInputCodes m_inputCode;

	virtual bool isValidID(event_id id);
};