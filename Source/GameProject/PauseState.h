#pragma once
#include "GameState.h"
#include "Button.h"
#include "Observer.h"
#include "Input.h"
#include <string>

class TextBar;

class PauseState :
	public GameState
{
public:
	static const std::string pause_message;
	static const unsigned short pause_font_height;
	static const float text_pos_x;
	static const float text_pos_y;
	static const float quit_button_x;
	static const float quit_button_y;
	static const float button_width;
	static const float button_height;
	static const unsigned short button_font_height;

	static const aie::EInputCodes unpause_key;

	PauseState(GameProjectApp* app);
	virtual ~PauseState();
	PauseState(const PauseState& other);
	PauseState& operator=(const PauseState& other);

	State* clone() const;

	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D* renderer);

	virtual void onEnter();

	


protected:
	std::unique_ptr<TextBar> m_pauseText;
	std::shared_ptr<Button> m_quitButton;
};

