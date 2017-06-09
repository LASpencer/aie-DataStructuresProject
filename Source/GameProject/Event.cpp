#include "stdafx.h"
#include "Event.h"

Event::Event(event_id id) : EventBase(id)
{
	if (!isValidID(id)) {
		throw std::invalid_argument("Invalid event ID");
	}
}

Event::~Event()
{
}

bool Event::isValidID(event_id id)
{
	return	id == destroyed ||
			id == frame_start ||
			id == state_entered ||
			id == state_exited ||
			id == gain_focus ||
			id == lose_focus ||
			id == timer_start ||
			id == timer_finished ||
			id == mouse_over ||
			id == mouse_exit ||
			id == clicked;
}
