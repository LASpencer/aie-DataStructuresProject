#pragma once


class EventBase {
public:
	enum event_id {
		//member_updated,		//Some variable was updated
		destroyed,			//Subject was destroyed
		frame_start,		//Subject has started new update
		state_entered,		//State was entered
		state_exited,		//State was exited
		gain_focus,			//State gained focus
		lose_focus,			//State lost focus
		timer_start,		//A timer was started
		timer_finished,		//A timer has finished
		mouse_over,			//The mouse cursor is over the subject
		mouse_exit,			//The mouse cursor has left the subject
		clicked				//The subject was clicked
	};

	EventBase(event_id id);
	virtual ~EventBase();

	event_id getEventID();

protected:
	event_id m_id;
	// Check if event id is possible for concrete class
	virtual bool isValidID(event_id id) = 0;
};