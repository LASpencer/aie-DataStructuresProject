#pragma once
#include "Component.h"

//TODO extract shared functionality from sprite to this
//TODO create derived MultiSprite component whichhas an array of textureptrs
class SpriteBase :
	public Component {
public:
	SpriteBase();
	SpriteBase(float width, float height, float uvx, float uvy, float uvw, float uvh,
				float xOrigin, float yOrigin);
	virtual ~SpriteBase();

	void setUVRect(float uvx, float uvy, float uvw, float uvh);
	void setDimensions(float width, float height);
	void setOrigin(float x, float y);

	virtual void update(Entity* entity, float deltaTime) {};
	virtual void draw(Entity* entity, aie::Renderer2D* renderer) = 0;

	virtual Identifier getID();

protected:
	float		m_uvx, m_uvy, m_uvw, m_uvh, m_width, m_height, m_xOrigin, m_yOrigin;
};