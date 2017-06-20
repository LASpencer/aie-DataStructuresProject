#include "stdafx.h"
#include "EntityFactory.h"
#include "GameProjectApp.h"
#include "MultiSprite.h"
#include "Collider.h"
#include "HeroController.h"
#include "Filepaths.h"

const float EntityFactory::hero_sprite_width = 46.0f;
const float EntityFactory::hero_sprite_height = 50.0f;


const std::string EntityFactory::hero_sprite_filepath = filepath::hero_blue;
const std::string EntityFactory::hero_robe_filepath = filepath::robe_brown;
const std::string EntityFactory::hero_armour_filepath = filepath::armour_samurai;
const std::string EntityFactory::hero_shield_filepath = filepath::shield_steel;
const std::string EntityFactory::hero_helmet_filepath = filepath::helmet_gold;
const std::string EntityFactory::sword_sprite_filepath = filepath::sword_rapier;

EntityFactory::EntityFactory(GameProjectApp* app) : m_app(app)
{
}

EntityFactory::~EntityFactory()
{
}

std::shared_ptr<Entity> EntityFactory::createEntity(EntityType type, glm::mat3 position)
{
	return createEntity(type, position, m_app->getSceneRoot());
}

std::shared_ptr<Entity> EntityFactory::createEntity(EntityType type, glm::mat3 position, std::shared_ptr<SceneObject> parent)
{
	//TODO create entity based on passed value and add it to app's list
	std::shared_ptr<Entity> entity;
	switch (type) {
	case(hero):
		entity = createHero(position, parent);
		break;
		//TODO functions for making floor, block, door
	default:
		break;
	}
	return entity;
}

std::shared_ptr<Entity> EntityFactory::createHero(glm::mat3 position, std::shared_ptr<SceneObject> parent)
{
	//TODO create hero
	EntityPtr hero = std::make_shared<Entity>();
	// Set position and place in scene graph
	SceneObjectPtr pos = hero->getPosition();
	pos->setLocalTransform(position);
	m_app->getSceneRoot()->addChild(pos);
	// Add components
	std::pair<float, float> startFrame = HeroController::animation_frames.at(HeroController::idle);
	las::Array<TexturePtr> textures({
		m_app->getResourceManager()->getTexture(hero_sprite_filepath),
		m_app->getResourceManager()->getTexture(hero_robe_filepath),
		m_app->getResourceManager()->getTexture(hero_armour_filepath),
		m_app->getResourceManager()->getTexture(hero_helmet_filepath),
		m_app->getResourceManager()->getTexture(hero_shield_filepath) });
	hero->addComponent(std::make_shared<MultiSprite>(textures,
		hero_sprite_width, hero_sprite_height, startFrame.first, startFrame.second,
		HeroController::sprite_uv_width, HeroController::sprite_uv_height));
	hero->addComponent(std::make_shared<Collider>());
	hero->addComponent(std::make_shared<HeroController>());
	//Set tags
	hero->addTag(Entity::player);
	m_app->getEntityList().push_back(hero);
	//TODO add a sword entity, child of the hero, to entity list after hero
	// hero has weakptr to it
	return hero;
}
