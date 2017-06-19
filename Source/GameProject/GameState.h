#pragma once
#include "State.h"
#include "Subject.h"
#include "EventManager.h"
#include "ResourceManager.h"
#include "Renderer2D.h"

class GameProjectApp;

class GameState :
	public StackState, public Subject
{
public:
	GameState(GameProjectApp* app);
	virtual ~GameState();

	GameState(const GameState& other);

	GameState& operator=(const GameState& other);

	virtual void update(float deltaTime) = 0;
	virtual void draw(aie::Renderer2D* renderer) = 0; //TODO pass in renderer2d?

	virtual void onEnter();
	virtual void onExit();
	virtual void onFocus();
	virtual void onLoseFocus();

	virtual void addObserver(std::shared_ptr<Observer> observer);
	virtual void removeObserver(std::shared_ptr<Observer> observer);
	virtual void clearObservers();
	virtual void notifyObservers(EventBase* event);
	virtual bool isSubscribed(const Observer* observer) const;

protected:
	GameProjectApp* m_app;
	EventManager m_eventManager;

};

