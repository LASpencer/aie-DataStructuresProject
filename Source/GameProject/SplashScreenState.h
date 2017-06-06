#pragma once
#include "GameState.h"
#include "ResourceManager.h"
class SplashScreenState :
	public GameState
{
public:
	static const float TIMER_DURATION;

	SplashScreenState(GameProjectApp* app);
	virtual ~SplashScreenState();
	SplashScreenState(const SplashScreenState& other);

	virtual State* clone() const;

	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D* renderer);
	virtual void onEnter();

protected:
	float m_timer;
	TexturePtr m_splashImage;
};

