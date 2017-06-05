#pragma once
#include "GameState.h"
class MainMenuState :
	public GameState
{
public:
	MainMenuState();
	virtual ~MainMenuState();
	MainMenuState(const MainMenuState& other);

	State* clone() const;
	//TODO
	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D* renderer);

	virtual void loadResources(ResourceManager* resourceManager);

protected:
	TexturePtr m_menuImage;
};

