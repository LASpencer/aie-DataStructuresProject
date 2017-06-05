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
	m_font = new aie::Font("./font/consolas.ttf", 32);
	m_textureManager = new ResourceManager<aie::Texture>();
	m_stateMachine = new GameStateMachine();
	m_stateMachine->loadTextures(m_textureManager);
	return true;
}

void GameProjectApp::shutdown() {

	delete m_stateMachine;
	delete m_textureManager;
	delete m_font;
	delete m_2dRenderer;
}

void GameProjectApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
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
	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 0);

	// done drawing sprites
	m_2dRenderer->end();
}