#pragma once
#include "GameState.h"
#include <string>

class TextBar;

class PauseState :
	public GameState
{
public:
	static const std::string pause_message;
	static const std::string pause_font_path;
	static const unsigned short pause_font_height;
	static const float text_pos_x;
	static const float text_pos_y;

	PauseState(GameProjectApp* app);
	virtual ~PauseState();
	PauseState(const PauseState& other);

	State* clone() const;

	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D* renderer);

protected:
	TextBar* m_pauseText;
};

