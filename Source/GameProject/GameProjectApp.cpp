#include "stdafx.h"
#include "GameProjectApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"


GameProjectApp::GameProjectApp() {

}

GameProjectApp::~GameProjectApp() {

}

bool GameProjectApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_resourceManager = new ResourceManager();
	m_stateMachine = new GameStateMachine(this);
	return true;
}

void GameProjectApp::shutdown() {

	delete m_stateMachine;
	delete m_resourceManager;
	delete m_2dRenderer;
}

void GameProjectApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	m_stateMachine->updateState();
	las::Stack<std::shared_ptr<GameState>> stack = m_stateMachine->getStateStack();
	while (!stack.empty()) {
		stack.pop()->update(deltaTime);
	}
}

void GameProjectApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	las::Stack<std::shared_ptr<GameState>> stack = m_stateMachine->getStateStack(true);
	while (!stack.empty()) {
		stack.pop()->draw(m_2dRenderer);
	}

	//fps info
	m_2dRenderer->setRenderColour(1, 1, 0, 1);
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText((m_resourceManager->getFont("./font/consolas.ttf", 32))->get(), fps, 0, 720 - 32);
	// done drawing sprites
	m_2dRenderer->end();
}

ResourceManager * GameProjectApp::getResourceManager()
{
	return m_resourceManager;
}
