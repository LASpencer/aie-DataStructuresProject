#pragma once
#include "SpriteBase.h"
#include "Array.h"
#include "ResourceManager.h"

class MultiSprite : public SpriteBase {
public:
	MultiSprite();
	MultiSprite(las::Array<TexturePtr>& textures, float width = 0.0f, float height = 0.0f,
		float uvx = 0.0f, float uvy = 0.0f, float uvw = 1.0f, float uvh = 1.0f,
		float xOrigin = 0.5f, float yOrigin = 0.5f);
	virtual ~MultiSprite();

	void setTextures(las::Array<TexturePtr>& textures);

	virtual void draw(Entity* entity, aie::Renderer2D* renderer);
protected:
	las::Array<TexturePtr>	m_textures;
};