#pragma once
#include "GameState.h"
#include "Button.h"
#include "Observer.h"

/*	State for displaying the main menu
	Exits to
*/
class MainMenuState :
	public GameState{
public:
	static const std::string title_message;
	static const float button_width;
	static const float button_height;
	static const float play_button_x;
	static const float play_button_y;
	static const float exit_button_x;
	static const float exit_button_y;
	static const float title_pos_x;
	static const float title_pos_y;
	static const unsigned short button_font_height;
	static const unsigned short title_font_height;

	MainMenuState(GameProjectApp* app);
	virtual ~MainMenuState();
	
	MainMenuState(const MainMenuState& other);

	MainMenuState& operator=(const MainMenuState& other);

	State* clone() const;

	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D* renderer);

	virtual void onEnter();

	virtual void onExit();

protected:
	TexturePtr m_menuImage;
	std::unique_ptr<TextBar> m_titleText;
	std::shared_ptr<Button> m_playButton;
	std::shared_ptr<Button> m_exitButton;
	int m_uvCol, m_uvRow;
	float m_timer;
	//TODO make this an observer, deal with buttons through events
};

