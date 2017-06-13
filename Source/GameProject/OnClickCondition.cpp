#include "stdafx.h"
#include "OnClickCondition.h"
#include "Subject.h"
#include "EventBase.h"
#include "InputEvent.h"

OnClickCondition::OnClickCondition() : m_clicked(false), m_subscribed(false), m_button(aie::INPUT_MOUSE_BUTTON_LEFT)
{
}

OnClickCondition::OnClickCondition(aie::EInputCodes button) : m_clicked(false), m_subscribed(false), m_button(button)
{
	if (button != aie::INPUT_MOUSE_BUTTON_LEFT ||
		button != aie::INPUT_MOUSE_BUTTON_MIDDLE ||
		button != aie::INPUT_MOUSE_BUTTON_RIGHT ||
		button != aie::INPUT_MOUSE_BUTTON_4 ||
		button != aie::INPUT_MOUSE_BUTTON_5 ||
		button != aie::INPUT_MOUSE_BUTTON_6 ||
		button != aie::INPUT_MOUSE_BUTTON_7 ||
		button != aie::INPUT_MOUSE_BUTTON_8) {
		throw std::invalid_argument("Button must be mouse button");
	}
}


OnClickCondition::~OnClickCondition()
{
}

OnClickCondition::OnClickCondition(const OnClickCondition & other) : EventCondition(other), m_clicked(false),m_subscribed(false)
{
}

EventCondition * OnClickCondition::clone() const
{
	return new OnClickCondition(*this);
}

bool OnClickCondition::test()
{
	return m_clicked;
}

void OnClickCondition::notify(Subject * subject, EventBase* event)
{	
	InputEvent* inputEvent = dynamic_cast<InputEvent*>(event);
	switch (event->getEventID()) {
	case(EventBase::event_id::clicked):
		assert(inputEvent != nullptr);
		if (inputEvent->getInputCode() == m_button) {
			m_clicked = true;
		}
		break;
	case(EventBase::event_id::frame_start):
		m_clicked = false;
	case(EventBase::event_id::destroyed):
		m_subscribed = false;
		break;
	default:
		break;
	}
}

bool OnClickCondition::addSubject(Subject* subject)
{
	if (m_subscribed) {
		return false;
	} else {
		m_subscribed = true;
		return true;
	}
}

void OnClickCondition::removeSubject(Subject * subject)
{
	m_subscribed = false;
}


