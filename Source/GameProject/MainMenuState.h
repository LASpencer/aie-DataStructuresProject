#pragma once
#include "GameState.h"
#include "Button.h"
#include "Observer.h"
class MainMenuState :
	public GameState, public Observer, public std::enable_shared_from_this<MainMenuState>
{
public:
	static const float play_button_x;
	static const float play_button_y;
	static const float exit_button_x;
	static const float exit_button_y;
	static const std::string button_font_path;
	static const unsigned short button_font_height;

	MainMenuState(GameProjectApp* app);
	virtual ~MainMenuState();
	MainMenuState(const MainMenuState& other);

	State* clone() const;

	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D* renderer);

	virtual void onEnter();

	virtual void notify(Subject* subject, EventBase* event);
	virtual bool addSubject(Subject* subject);
	virtual void removeSubject(Subject* subject);

protected:
	TexturePtr m_menuImage;
	std::shared_ptr<Button> m_playButton;
	std::shared_ptr<Button> m_exitButton;

	//TODO overload CopyConditionIfSubscribed to also care about buttons
};

