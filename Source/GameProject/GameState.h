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

	virtual void update(float deltaTime) = 0;
	virtual void draw(aie::Renderer2D* renderer) = 0; //TODO pass in renderer2d?

	virtual void onEnter();
	virtual void onExit();
	virtual void onFocus();
	virtual void onLoseFocus();

	virtual void addObserver(std::shared_ptr<Observer> observer);
	virtual void removeObserver(std::shared_ptr<Observer> observer);
	virtual void notifyObservers(EventBase* event);
	virtual bool isSubscribed(const Observer* observer) const;

protected:
	bool m_focus;
	GameProjectApp* m_app;
	EventManager m_eventManager;

	/** Creates a copy of a condition if it relies on a subscription to another GameState
	* @param condition a condition
	* @param other another GameState which may hold a subscription to condition
	* @return false, or true and shared_ptr to new Condition if condition was subscribed to Other*/
	virtual std::pair<bool,std::shared_ptr<Condition>> copyConditionIfSubscribed(std::shared_ptr<const Condition> condition, const GameState& other);
};

