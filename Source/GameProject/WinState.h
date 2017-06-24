#pragma once
#include "GameState.h"
#include "TextBar.h"
#include "Button.h"
#include "Observer.h"
#include <string>

/*	Displays victory message and prompts player to replay the game

	Transitions to MainMenuState on clicking menu button
	Transitions to FinalState on clicking quit button
*/
class WinState :
	public GameState, public Observer {
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
	
	static const float music_volume;

	static const std::string button_font_path;
	static const unsigned short button_font_height;

	WinState(GameProjectApp* app);
	virtual ~WinState();

	WinState(const WinState& other);

	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D* renderer);

	virtual void onEnter();
	virtual void onExit();

	virtual void notify(Subject* subject, EventBase* event);
	virtual bool addSubject(Subject* subject);
	virtual void removeSubject(Subject* subject);
protected:
	TexturePtr	m_winImage;
	AudioPtr	m_music;
	std::unique_ptr<TextBar> m_winText;
	std::shared_ptr<Button> m_menuButton;
	std::shared_ptr<Button> m_quitButton;
};