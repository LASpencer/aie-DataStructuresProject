#pragma once
#include "GameState.h"

class Ship;//HACK for testing

class BattleState :
	public GameState
{
public:
	BattleState(GameProjectApp* app);
	virtual ~BattleState();
	BattleState(const BattleState& other);

	State* clone() const;

	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D* renderer);

	virtual void onEnter();
	virtual void onExit();

protected:
	TexturePtr m_battleImage;

	//HACK for testing
	Ship* ship;
};

