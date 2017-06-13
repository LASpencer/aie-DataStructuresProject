#pragma once
#include "Component.h"
#include "ResourceManager.h"


class Sprite :
	public Component
{
public:
	Sprite();
	Sprite(TexturePtr texture);
	~Sprite();

	void setTexture(TexturePtr texture);
	void update(Entity* entity, float deltaTime) {};
	void draw(Entity* entity, aie::Renderer2D* renderer);
	//T
	virtual Identifier getID();

	//TODO: Animated sprite using UVRect
protected:
	TexturePtr m_texture;
};

//TODO map of enumerated stances to UVRect values