#pragma once
#include "Input.h"
#include "GameState.h"
#include "ResourceManager.h"

class Hero;

class BattleState :
	public GameState
{
public:
	static const aie::EInputCodes pause_key;

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
};

