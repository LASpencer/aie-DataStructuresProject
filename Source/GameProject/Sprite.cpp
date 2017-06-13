#include "stdafx.h"
#include "Entity.h"
#include "Sprite.h"
#include "SceneObject.h"

Sprite::Sprite() : m_texture(), m_uvx(0),m_uvy(0),m_uvw(1.0f),m_uvh(1.0f), m_width(0),m_height(0),m_xOrigin(0.5f),m_yOrigin(0.5f)
{
}

Sprite::Sprite(TexturePtr texture, float width, float height, float uvx, float uvy, float uvw, float uvh, float xOrigin, float yOrigin)
	: m_texture(texture), m_width(width),m_height(height), m_uvx(uvx), m_uvy(uvy), m_uvw(uvw), m_uvh(uvh), m_xOrigin(xOrigin), m_yOrigin(yOrigin)
{
	if (uvx < 0.0f || uvx > 1.0f ||
		uvy < 0.0f || uvy > 1.0f ||
		uvw < 0.0f || uvw > 1.0f ||
		uvh < 0.0f || uvh > 1.0f ) {
		throw std::invalid_argument("UVRect parameters must be between 0 and 1");
	}
}


Sprite::~Sprite()
{
}

void Sprite::setTexture(TexturePtr texture)
{
	m_texture = texture;
}

void Sprite::setUVRect(float uvx, float uvy, float uvw, float uvh)
{
	if (uvx < 0.0f || uvx > 1.0f ||
		uvy < 0.0f || uvy > 1.0f ||
		uvw < 0.0f || uvw > 1.0f ||
		uvh < 0.0f || uvh > 1.0f ) {
		throw std::invalid_argument("UVRect parameters must be between 0 and 1");
	}
	m_uvx = uvx;
	m_uvy = uvy;
	m_uvw = uvw;
	m_uvh = uvh;
}

void Sprite::setDimensions(float width, float height)
{
	m_width = width;
	m_height = height;
}

void Sprite::setOrigin(float x, float y)
{
	m_xOrigin = x;
	m_yOrigin = y;
}

void Sprite::draw(Entity * entity, aie::Renderer2D* renderer)
{
	SceneObject* sceneObject = std::dynamic_pointer_cast<SceneObject>(entity->getComponent(scene_object)).get();
	if (sceneObject == nullptr) {
		throw std::invalid_argument("Sprite requires SceneObject component");
		//TODO create invalid argument subclass for missing component dependency
	}
	//TODO: Sprite can have origin point set
	//TODO figure out correct matrix pointer cast
	renderer->setUVRect(m_uvx, m_uvy, m_uvw, m_uvh);
	renderer->drawSpriteTransformed3x3(m_texture->get(), &sceneObject->getGlobalTransform()[0][0], m_width,m_height,0,m_xOrigin,m_yOrigin);//TODO fix bug where uvrect sprite is size of entire sheet
}

Sprite::Identifier Sprite::getID()
{
	return sprite;
}
