#include "stdafx.h"
#include "gl_core_4_4.h"
#include "GameProjectApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Filepaths.h"


GameProjectApp::GameProjectApp() : m_entityList()
{

}

GameProjectApp::~GameProjectApp() {
	//TODO fix sceneObject memory bug
}

bool GameProjectApp::startup() {
	
	m_2dRenderer = new aie::Renderer2D();
	m_resourceManager = new ResourceManager();
	m_stateMachine = new GameStateMachine(this);
	m_entityFactory = new EntityFactory(this);
	m_sceneRoot = std::make_shared<SceneObject>();
	// Disable face culling, so sprites can be flipped
	glDisable(GL_CULL_FACE);
	return true;
}

void GameProjectApp::shutdown() {

	// Release any surviving shared pointers, instead of waiting for destruction
	m_entityList.clear();
	m_sceneRoot.reset();
	delete m_entityFactory;
	delete m_stateMachine;
	delete m_resourceManager;
	delete m_2dRenderer;
}

void GameProjectApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();

	m_stateMachine->update(deltaTime);
}

void GameProjectApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// Reset UVRect to full texture
	m_2dRenderer->setUVRect(0, 0, 1, 1);
	m_stateMachine->draw(m_2dRenderer);

	//fps info
	m_2dRenderer->setRenderColour(1, 1, 0, 1);
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText((m_resourceManager->getFont(filepath::consolas_path, 32))->get(), fps, 0, 720 - 32);
	// done drawing sprites
	m_2dRenderer->end();
}

ResourceManager * GameProjectApp::getResourceManager()
{
	return m_resourceManager;
}

EntityFactory * GameProjectApp::getEntityFactory()
{
	return m_entityFactory;
}

SceneObjectPtr GameProjectApp::getSceneRoot()
{
	return m_sceneRoot;
}

las::Array<EntityPtr>& GameProjectApp::getEntityList()
{
	return m_entityList;
}
