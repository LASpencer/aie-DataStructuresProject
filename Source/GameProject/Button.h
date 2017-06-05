#pragma once
#include "TextBar.h"
#include "Subject.h"
#include "EventManager.h"

class Button :
	public TextBar, public Subject
{
public:
	Button();
	~Button();

	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D* renderer);

	virtual void addObserver(std::shared_ptr<Observer> observer);
	virtual void removeObserver(std::shared_ptr<Observer> observer);
	virtual void notifyObservers(int eventID);
	virtual bool isSubscribed(const Observer* observer) const;

protected:
	bool m_pressed;
	bool m_hover;
	unsigned int m_hoverColour;
	unsigned int m_pressedColour;
	EventManager m_eventManager;
};

