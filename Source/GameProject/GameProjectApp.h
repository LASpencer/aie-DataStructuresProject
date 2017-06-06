#pragma once
#include "stdafx.h"

#include "Application.h"
#include "Renderer2D.h"
#include "ResourceManager.h"
#include "GameStateMachine.h"

class GameProjectApp : public aie::Application {
public:

	GameProjectApp();
	virtual ~GameProjectApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	ResourceManager* getResourceManager();

protected:

	aie::Renderer2D*	m_2dRenderer;
	ResourceManager*	m_resourceManager;
	GameStateMachine*	m_stateMachine;

};