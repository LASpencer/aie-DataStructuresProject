#pragma once
#include "TextBar.h"
#include "Subject.h"
#include "EventManager.h"

class Button :
	public Subject
{
public:
	static const unsigned int def_button_colour;
	static const unsigned int def_hover_colour;
	static const unsigned int def_pressed_colour;
	static const float def_width;
	static const float def_height;

	Button( float x = 0, float y = 0, float width = def_width, float height = def_height, unsigned int colour = def_button_colour,
		unsigned int hoverColour = def_hover_colour, unsigned int pressedColour = def_pressed_colour);
	~Button();

	void setPosition(float x, float y);
	void setDimensions(float width, float height);
	void setColour(unsigned int colour);
	void setHoverColour(unsigned int colour);
	void setPressedColour(unsigned int colour);

	bool isPressed();
	void setPressed(bool press);

	void reset();

	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D* renderer);

	virtual void addObserver(std::shared_ptr<Observer> observer);
	virtual void removeObserver(std::shared_ptr<Observer> observer);
	virtual void notifyObservers(EventBase* event);
	virtual bool isSubscribed(const Observer* observer) const;

protected:
	float m_xPos, m_yPos, m_xExtent, m_yExtent;
	bool m_pressed;
	bool m_hover;
	unsigned int m_colour;
	unsigned int m_hoverColour;
	unsigned int m_pressedColour;
	EventManager m_eventManager;
	//TODO derived class: button with content, can contain textbar or sprite and 
};

