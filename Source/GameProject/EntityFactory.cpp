#include "stdafx.h"
#include "EntityFactory.h"
#include "GameProjectApp.h"
#include "Sprite.h"
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

//TODO extract out to filepath.h
const std::string EntityFactory::block_sprite_filepath = "./textures/rock_large.png";

EntityFactory::EntityFactory(GameProjectApp* app) : m_app(app)
{
}

EntityFactory::~EntityFactory()
{
}

EntityPtr EntityFactory::createEntity(EntityType type, glm::mat3 position)
{
	return createEntity(type, position, m_app->getSceneRoot());
}

EntityPtr EntityFactory::createEntity(EntityType type, glm::mat3 position, SceneObjectPtr parent)
{
	//TODO create entity based on passed value and add it to app's list
	EntityPtr entity;
	switch (type) {
	case(hero):
		entity = createHero(position, parent);
		break;
	case(block):
		entity = createBlock(position, parent);
		break;
		//TODO functions for making floor, block, door
	default:
		break;
	}
	return entity;
}

EntityPtr EntityFactory::createHero(glm::mat3 position, SceneObjectPtr parent)
{
	//TODO create hero
	EntityPtr hero = std::make_shared<Entity>();
	// Set position and place in scene graph
	setEntityPosition(hero, position, parent);
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

EntityPtr EntityFactory::createBlock(glm::mat3 position, SceneObjectPtr parent)
{
	EntityPtr block = std::make_shared<Entity>();
	setEntityPosition(block, position, parent);
	// Add components
	block->addComponent(std::make_shared<Sprite>(m_app->getResourceManager()->getTexture(block_sprite_filepath)));
	std::shared_ptr<Collider> collider = std::make_shared<Collider>();
	collider->setBoxes({ { {-35,-38}, {35,38},BoxType::body } });
	block->addComponent(collider);
	// Set tags
	block->addTag(Entity::block);
	m_app->getEntityList().push_back(block);
	return block;
}

bool EntityFactory::setEntityPosition(EntityPtr entity, glm::mat3 position, SceneObjectPtr parent)
{
	SceneObjectPtr pos = entity->getPosition();
	pos->setLocalTransform(position);
	return m_app->getSceneRoot()->addChild(pos);
}
