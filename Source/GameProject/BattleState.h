#pragma once
#include "GameState.h"
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

protected:
	TexturePtr m_battleImage;
};

