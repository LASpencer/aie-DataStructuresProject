#include "stdafx.h"
#include "MultiSprite.h"
#include "SceneObject.h"
#include "Entity.h"

MultiSprite::MultiSprite() : SpriteBase(), m_textures()
{
}

MultiSprite::MultiSprite(las::Array<TexturePtr>& textures, float width, float height, float uvx, float uvy, float uvw, float uvh, float xOrigin, float yOrigin)
	: SpriteBase(width, height, uvx, uvy, uvw, uvh, xOrigin, yOrigin), m_textures(textures)
{
}

MultiSprite::~MultiSprite()
{
}

void MultiSprite::setTextures(las::Array<TexturePtr>& textures)
{
	m_textures = textures;
}

void MultiSprite::draw(Entity * entity, aie::Renderer2D * renderer)
{
	SceneObject* sceneObject = std::dynamic_pointer_cast<SceneObject>(entity->getComponent(scene_object)).get();
	if (sceneObject == nullptr) {
		throw missing_component("Sprite requires SceneObject component");
		//TODO create invalid argument subclass for missing component dependency
	}
	renderer->setUVRect(m_uvx, m_uvy, m_uvw, m_uvh);
	for (TexturePtr texture : m_textures) {
		renderer->drawSpriteTransformed3x3(texture->get(), &sceneObject->getGlobalTransform()[0][0], m_width, m_height, 0, m_xOrigin, m_yOrigin);//TODO fix bug where uvrect sprite is size of entire sheet

	}
}
