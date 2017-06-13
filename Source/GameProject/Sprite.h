#pragma once
#include "Component.h"
#include "ResourceManager.h"


class Sprite :
	public Component
{
public:
	Sprite();
	Sprite(TexturePtr texture,float width = 0.0f, float height = 0.0f, float uvx = 0.0f, float uvy = 0.0f, float uvw = 1.0f, float uvh = 1.0f, float xOrigin = 0.5f, float yOrigin = 0.5f);
	~Sprite();

	void setTexture(TexturePtr texture);
	void setUVRect(float uvx, float uvy, float uvw, float uvh);
	void setDimensions(float width, float height);
	void setOrigin(float x, float y);

	void update(Entity* entity, float deltaTime) {};
	void draw(Entity* entity, aie::Renderer2D* renderer);
	//T
	virtual Identifier getID();

	//TODO: Animated sprite using UVRect
protected:
	//TODO sprite has array of texturePtr, each drawn above the last
	TexturePtr m_texture;
	float		m_uvx, m_uvy, m_uvw, m_uvh, m_width, m_height, m_xOrigin, m_yOrigin;
	//TODO include width, height, x and y origin
};

//TODO map of enumerated stances to UVRect values