#pragma once
#include "EventCondition.h"
class OnClickCondition :
	public EventCondition
{
public:
	OnClickCondition();
	~OnClickCondition();
	OnClickCondition(const OnClickCondition& other);

	EventCondition* clone() const;
	virtual bool test();

	virtual void notify(Subject* subject, int eventID);

	virtual bool addSubject(Subject* subject);
	virtual void removeSubject(Subject* subject);

protected:
	bool m_clicked;
	bool m_subscribed;
	//TODO condition holds map of subject*, bool. Returns true if any were clicked
};

