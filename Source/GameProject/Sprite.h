#pragma once
#include "Component.h"
#include "ResourceManager.h"

class Sprite :
	public Component
{
public:
	Sprite();
	~Sprite();
protected:
	TexturePtr m_texture;
};

