#pragma once
#include "EventCondition.h"
#include "Input.h"
class OnClickCondition :
	public EventCondition
{
public:
	OnClickCondition();
	OnClickCondition(aie::EInputCodes button);
	~OnClickCondition();
	OnClickCondition(const OnClickCondition& other);

	EventCondition* clone() const;
	virtual bool test();

	virtual void notify(Subject* subject, EventBase* event);

	virtual bool addSubject(Subject* subject);
	virtual void removeSubject(Subject* subject);

protected:
	bool m_clicked;
	bool m_subscribed;
	aie::EInputCodes m_button;
	//TODO condition holds map of subject*, bool. Returns true if any were clicked
};

