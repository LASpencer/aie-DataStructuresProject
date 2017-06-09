#include "stdafx.h"
#include "Entity.h"
#include "Sprite.h"
#include "SceneObject.h"

Sprite::Sprite() : m_texture()
{
}

Sprite::Sprite(TexturePtr texture) : m_texture(texture)
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
		throw std::invalid_argument("Sprite requires SceneObject component");
		//TODO create invalid argument subclass for missing component dependency
	}
	//TODO: Sprite can have origin point set
	//TODO figure out correct matrix pointer cast
	renderer->drawSpriteTransformed3x3(m_texture->get(), &sceneObject->getGlobalTransform()[0][0]); //HACK is this intended? Ask for help
}

Sprite::Identifier Sprite::getID()
{
	return sprite;
}
