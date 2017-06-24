#pragma once
#include "stdafx.h"

#include "Application.h"
#include "Renderer2D.h"
#include "ResourceManager.h"
#include "GameStateMachine.h"
#include "Entity.h"
#include "EntityFactory.h"

class GameProjectApp : public aie::Application {
public:

	GameProjectApp();
	virtual ~GameProjectApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	ResourceManager* getResourceManager();
	EntityFactory* getEntityFactory();
	SceneObjectPtr getSceneRoot();
	las::Array<EntityPtr>& getEntityList();

protected:

	aie::Renderer2D*	m_2dRenderer;
	ResourceManager*	m_resourceManager;
	GameStateMachine*	m_stateMachine;
	las::Array<EntityPtr>	m_entityList;
	EntityFactory*		m_entityFactory;
	SceneObjectPtr		m_sceneRoot;
};