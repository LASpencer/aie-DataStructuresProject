#pragma once
#include "Entity.h"

//HACK just to test entity components, probably will make something else later
class Ship :public Entity {
public:
	Ship();
	virtual ~Ship();

	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D* renderer);
};