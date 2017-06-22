#pragma once
#include "Input.h"
#include "GameState.h"
#include "ResourceManager.h"
#include "Component.h"
#include "Observer.h"

class Hero;

class BattleState :
	public GameState, public Observer
{
public:
	static const aie::EInputCodes pause_key;
	static const aie::EInputCodes toggle_hitboxes_key;

	BattleState(GameProjectApp* app);
	virtual ~BattleState();
	BattleState(const BattleState& other);
	BattleState& operator=(const BattleState& other);

	State* clone() const;

	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D* renderer);

	virtual void onEnter();
	virtual void onExit();

	virtual void notify(Subject* subject, EventBase* event) ;
	virtual bool addSubject(Subject* subject);
	virtual void removeSubject(Subject* subject);

protected:
	TexturePtr m_battleImage;

	las::Array<EntityPtr> getEntitiesWithComponent(Component::Identifier component, las::Array<EntityPtr>::iterator first, las::Array<EntityPtr>::iterator last);
};

