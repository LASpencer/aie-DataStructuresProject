#pragma once
#include "GameState.h"
#include "Button.h"
#include "Observer.h"

/*	State for displaying the main menu. Music and an animated background play
	until player clicks a button

	Transitions to BattleState on clicking Play button
	Transitions to FinalState on clicking Exit button
*/
class MainMenuState :
	public GameState, public Observer{
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

	virtual void notify(Subject* subject, EventBase* event);
	virtual bool addSubject(Subject* subject);
	virtual void removeSubject(Subject* subject);

protected:
	TexturePtr m_menuImage;
	AudioPtr m_music;
	std::unique_ptr<TextBar> m_titleText;
	std::shared_ptr<Button> m_playButton;
	std::shared_ptr<Button> m_exitButton;
	int m_uvCol, m_uvRow;					// UVRect position of frame in background image
	float m_timer;
	//TODO make this an observer, deal with buttons through events
};

