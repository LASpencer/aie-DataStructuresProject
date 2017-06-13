#include "stdafx.h"
#include "Entity.h"
#include "Sprite.h"
#include "SceneObject.h"

Sprite::Sprite() : SpriteBase(), m_texture()
{
}

Sprite::Sprite(TexturePtr texture, float width, float height, float uvx, float uvy, float uvw, float uvh, float xOrigin, float yOrigin)
	: SpriteBase(width,height,uvx,uvy,uvw,uvh,xOrigin,yOrigin), m_texture(texture)
{
}


Sprite::~Sprite()
{
}

void Sprite::setTexture(TexturePtr texture)
{
	m_texture = texture;
}


void Sprite::draw(Entity * entity, aie::Renderer2D* renderer)
{
	SceneObject* sceneObject = std::dynamic_pointer_cast<SceneObject>(entity->getComponent(scene_object)).get();
	if (sceneObject == nullptr) {
		throw missing_component("Sprite requires SceneObject component");
		//TODO create invalid argument subclass for missing component dependency
	}
	//TODO: Sprite can have origin point set
	//TODO figure out correct matrix pointer cast
	renderer->setUVRect(m_uvx, m_uvy, m_uvw, m_uvh);
	renderer->drawSpriteTransformed3x3(m_texture->get(), &sceneObject->getGlobalTransform()[0][0], m_width,m_height,0,m_xOrigin,m_yOrigin);//TODO fix bug where uvrect sprite is size of entire sheet
}
