#pragma once
#include "GameState.h"
#include "ResourceManager.h"
class SplashScreenState :
	public GameState
{
public:
	static const float splash_duration;

	SplashScreenState(GameProjectApp* app);
	virtual ~SplashScreenState();
	SplashScreenState(const SplashScreenState& other);
	SplashScreenState& operator=(const SplashScreenState& other);

	virtual State* clone() const;

	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D* renderer);
	virtual void onEnter();

	virtual void onExit();

protected:
	float m_timer;
	bool m_resourcesLoaded, m_splashShown;
	TexturePtr m_splashImage;
	AudioPtr m_music;
};

