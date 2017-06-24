#pragma once
#include "GameState.h"
#include "TextBar.h"
#include "ResourceManager.h"

/*	Splash Sceen displays splash image and loads assets
	As this state doesn't use any animations or respond to user
	input, assets are loaded here to avoid noticable load times later.

	Transitons to MainMenuState if all assets have loaded and either timer
	runs out or the player presses any key
*/
class SplashScreenState :
	public GameState
{
public:
	static const float splash_duration;
	static const float load_pos_x;
	static const float load_pos_y;
	static const unsigned short load_font_height;

	static const std::string load_bg_msg;
	static const std::string load_sprite_msg;
	static const std::string load_audio_msg;
	static const std::string load_done_msg;

	SplashScreenState(GameProjectApp* app);
	virtual ~SplashScreenState();
	SplashScreenState(const SplashScreenState& other);
	SplashScreenState& operator=(const SplashScreenState& other);


	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D* renderer);
	virtual void onEnter();

	virtual void onExit();

protected:
	float m_timer;
	bool m_audioLoaded, m_backgroundLoaded, m_spritesLoaded;
	std::unique_ptr<TextBar> m_loadText;
	TexturePtr m_splashImage;
	AudioPtr m_music;
};

