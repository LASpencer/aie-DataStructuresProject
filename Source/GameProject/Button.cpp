#include "stdafx.h"
#include "Button.h"
#include "Renderer2D.h"
#include "Input.h"

const unsigned int Button::def_button_colour = 0x3030c0ff;
const unsigned int Button::def_hover_colour = 0x4040e0ff;
const unsigned int Button::def_pressed_colour = 0x202080ff;
const unsigned int Button::def_text_colour = 0xc0c030ff;
const float Button::def_width = 100.0f;
const float Button::def_height = 40.0f;



Button::Button(FontPtr font, std::string content, float x, float y, float width, float height, unsigned int textColour, unsigned int colour, unsigned int hoverColour, unsigned int pressedColour)
	: m_font(font), m_content(content), m_xPos(x), m_yPos(y), m_xExtent(width * 0.5f), m_yExtent(height * 0.5f), m_textColour(textColour), m_colour(colour), m_hoverColour(hoverColour), m_pressedColour(pressedColour), m_hover(false), m_pressed(false), m_eventManager(this)

{
}

Button::~Button()
{
	notifyObservers(destroyed);
}

void Button::setPosition(float x, float y)
{
	m_xPos = x;
	m_yPos = y;
}

void Button::setDimensions(float width, float height)
{
	m_xExtent = width * 0.5f;
	m_yExtent = height * 0.5f;
}

void Button::setColour(unsigned int colour)
{
	m_colour = colour;
}

void Button::setHoverColour(unsigned int colour)
{
	m_hoverColour = colour;
}

void Button::setPressedColour(unsigned int colour)
{
	m_pressedColour = colour;
}

void Button::setTextColour(unsigned int colour)
{
	m_textColour = colour;
}

void Button::setContent(const char * content)
{
	m_content = content;
}

void Button::setContent(const std::string & content)
{
	m_content = content;
}

void Button::setFont(FontPtr font)
{
	assert((*font).get() != nullptr);
	m_font = font;
}

bool Button::isPressed()
{
	return m_pressed;
}

void Button::setPressed(bool pressed)
{
	m_pressed = pressed;
}

void Button::reset()
{
	m_pressed = false;
	m_hover = false;
}

void Button::update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();
	int mouseX, mouseY;
	input->getMouseXY(&mouseX, &mouseY);
	notifyObservers(frame_start);
	// Check collision with button
	if (abs(m_xPos - mouseX) < m_xExtent && abs(m_yPos - mouseY) < m_yExtent) {
		if (!m_hover) {
			notifyObservers(mouse_over);
		}
		m_hover = true;
		// Check for click
		if (input->wasMouseButtonPressed(aie::INPUT_MOUSE_BUTTON_LEFT)) {
			m_pressed = !m_pressed;		//toggle state
			notifyObservers(clicked);
		}
	} else {
		if (m_hover) {
			notifyObservers(mouse_exit);
		}
		m_hover = false;
	}
}

void Button::draw(aie::Renderer2D * renderer)
{
	if (m_pressed) {
		renderer->setRenderColour(m_pressedColour);
	} else if (m_hover){
		renderer->setRenderColour(m_hoverColour);
	} else {
		renderer->setRenderColour(m_colour);
	}
	renderer->drawBox(m_xPos, m_yPos, m_xExtent * 2.0f, m_yExtent * 2.0f);
	if (!m_content.empty()) {
		float width, height;
		(*m_font)->getStringSize(m_content.c_str(), width, height);
		renderer->setRenderColour(m_textColour);
		renderer->drawText((*m_font).get(), m_content.c_str(), m_xPos - (width / 2.0f), m_yPos - (height / 4.0f));//TODO test this is right height
	}
	renderer->setRenderColour(0xffffffff);
}

void Button::addObserver(std::shared_ptr<Observer> observer)
{
	m_eventManager.addObserver(observer);
}

void Button::removeObserver(std::shared_ptr<Observer> observer)
{
	m_eventManager.removeObserver(observer);
}

void Button::notifyObservers(int eventID)
{
	m_eventManager.notifyObservers(eventID);
}

bool Button::isSubscribed(const Observer * observer) const
{
	return m_eventManager.isSubscribed(observer);
}
