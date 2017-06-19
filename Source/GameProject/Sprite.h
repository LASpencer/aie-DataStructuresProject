#pragma once
#include "SpriteBase.h"
#include "ResourceManager.h"


class Sprite :
	public SpriteBase
{
public:
	Sprite();
	Sprite(TexturePtr texture,float width = 0.0f, float height = 0.0f, 
		float uvx = 0.0f, float uvy = 0.0f, float uvw = 1.0f, float uvh = 1.0f, 
		float xOrigin = 0.5f, float yOrigin = 0.5f);
	virtual ~Sprite();

	void setTexture(TexturePtr texture);



	virtual void draw(aie::Renderer2D* renderer);
	//T
	

	//TODO: Animated sprite using UVRect
protected:
	//TODO sprite has array of texturePtr, each drawn above the last
	TexturePtr m_texture;
	
	//TODO include width, height, x and y origin
};

//TODO map of enumerated stances to UVRect values