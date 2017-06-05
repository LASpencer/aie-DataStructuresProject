#include "stdafx.h"
#include "MainMenuState.h"

MainMenuState::MainMenuState() : GameState()
{
}


MainMenuState::~MainMenuState()
{
}

MainMenuState::MainMenuState(const MainMenuState & other) : GameState(other)
{
}

State * MainMenuState::clone() const
{
	return new MainMenuState(*this);
}

void MainMenuState::update(float deltaTime)
{
	//TODO select menu options
}

void MainMenuState::draw(aie::Renderer2D* renderer)
{
	//TODO draw menu
	renderer->drawSprite(m_menuImage->get(), 640, 360);
}

void MainMenuState::loadTextures(ResourceManager<aie::Texture>* textureManager)
{
	m_menuImage = textureManager->get("./textures/mainMenu.png");
}
