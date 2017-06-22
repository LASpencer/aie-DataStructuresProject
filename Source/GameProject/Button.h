#pragma once
#include "TextBar.h"
#include "Subject.h"
#include "EventManager.h"
#include "ResourceManager.h"

class Button :
	public Subject
{
public:
	static const unsigned int def_button_colour;
	static const unsigned int def_hover_colour;
	static const unsigned int def_pressed_colour;
	static const unsigned int def_text_colour;
	static const float def_width;
	static const float def_height;

	Button(FontPtr font, std::string content = "", float x = 0, float y = 0, float width = def_width, float height = def_height, unsigned int textColour = def_text_colour, unsigned int colour = def_button_colour,
		unsigned int hoverColour = def_hover_colour, unsigned int pressedColour = def_pressed_colour);
	~Button();

	Button(const Button& other);

	Button& operator=(const Button& other);

	void setPosition(float x, float y);
	void setDimensions(float width, float height);
	void setColour(unsigned int colour);
	void setHoverColour(unsigned int colour);
	void setPressedColour(unsigned int colour);

	/** Sets colour of text
	* @param colour RGBA value as 4 byte integer*/
	void setTextColour(unsigned int colour);

	// Set content displayed in text bar
	void setContent(const char* content);
	void setContent(const std::string& content);

	/** Sets font of text
	* @param font FontPtr to true type font*/
	void setFont(FontPtr font);

	bool isPressed();
	void setPressed(bool press);

	void reset();

	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D* renderer);

	virtual void addObserver(std::shared_ptr<Observer> observer);
	virtual void removeObserver(std::shared_ptr<Observer> observer);
	virtual void clearObservers();
	virtual void notifyObservers(EventBase* event);
	virtual bool isSubscribed(const Observer* observer) const;

protected:
	float			m_xPos, m_yPos, m_xExtent, m_yExtent;
	bool			m_pressed, m_hover;
	unsigned int	m_colour;
	unsigned int	m_hoverColour;
	unsigned int	m_pressedColour;
	unsigned int	m_textColour;
	EventManager	m_eventManager;
	FontPtr			m_font;
	std::string		m_content;
	//TODO derived class: button with content, can contain textbar or sprite and 
};

