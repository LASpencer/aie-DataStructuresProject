#include "stdafx.h"
#include "InputEvent.h"

InputEvent::InputEvent(event_id id, aie::EInputCodes inputCode) : EventBase(id), m_inputCode(inputCode)
{
	if (!isValidID(id)) {
		throw std::invalid_argument("Invalid event ID");
	}
}

InputEvent::~InputEvent()
{
}

aie::EInputCodes InputEvent::getInputCode()
{
	return m_inputCode;
}


bool InputEvent::isValidID(event_id id)
{
	return	id == clicked ||
			id == mouse_release ||
			id == key_press ||
			id == key_release;
}
