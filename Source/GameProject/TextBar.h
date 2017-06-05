#pragma once
#include "ResourceManager.h"

class TextBar
{
public:
	TextBar();
	//TODO value ctor
	~TextBar();

	void setPosition(float x, float y);
	void setMessage(const char* message);
	void setMessage(std::string message);
	void setBoxColour(unsigned int colour);
	void setTextColour(unsigned int colour);
	void setFont(FontPtr font);//TODO also calculate char width, height
	virtual void update(float deltaTime) {};
	virtual void draw(aie::Renderer2D* renderer);
	//TODO const default values
protected:
	char* m_content;
	float m_xPos;
	float m_yPos;
	float m_charHeight;
	float m_charWidth;
	unsigned int m_boxColour;
	unsigned int m_textColour;
	FontPtr m_font;
};

