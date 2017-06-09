#include "stdafx.h"
#include "Ship.h"
#include "SceneObject.h"
#include "Sprite.h"

Ship::Ship() : Entity()
{
}

Ship::~Ship()
{
}

void Ship::update(float deltaTime)
{
	Entity::update(deltaTime);
}

void Ship::draw(aie::Renderer2D * renderer)
{
	Entity::draw(renderer);
}
