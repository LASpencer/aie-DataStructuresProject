#pragma once
#include "GameState.h"
#include "TextBar.h"
#include "Button.h"
#include <string>

class WinState :
	public GameState {
public:
	static const std::string win_message;
	static const std::string win_font_path;
	static const unsigned short win_font_height;
	static const float text_pos_x;
	static const float text_pos_y;
	static const float menu_button_x;
	static const float menu_button_y;
	static const float quit_button_x;
	static const float quit_button_y;
	static const float button_width;
	static const float button_height;
	static const std::string button_font_path;
	static const unsigned short button_font_height;

	WinState(GameProjectApp* app);
	virtual ~WinState();

	WinState(const WinState& other);

	State* clone() const;

	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D* renderer);

	virtual void onEnter();
	virtual void onExit();
protected:
	TexturePtr	m_winImage;
	AudioPtr	m_music;
	std::unique_ptr<TextBar> m_winText;
	std::shared_ptr<Button> m_menuButton;
	std::shared_ptr<Button> m_quitButton;
};