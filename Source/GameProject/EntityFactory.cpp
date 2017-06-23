#include "stdafx.h"
#include "EntityFactory.h"
#include "GameProjectApp.h"
#include "Sprite.h"
#include "MultiSprite.h"
#include "Collider.h"
#include "HeroController.h"
#include "Filepaths.h"

const float EntityFactory::hero_sprite_width = 92.0f;
const float EntityFactory::hero_sprite_height = 100.0f;

const float EntityFactory::block_sprite_width = 64.f;
const float EntityFactory::block_sprite_height = 64.f;


const float EntityFactory::door_sprite_width = 128.f;
const float EntityFactory::door_sprite_height = 184.f;

const float EntityFactory::door_uvx = 8.f/15.f;
const float EntityFactory::door_uvy = 6.f/11.f;
const float EntityFactory::door_uvw = 2.f/15.f;
const float EntityFactory::door_uvh = 3.f/11.f;

const float EntityFactory::block_uvx = 1.f / 15.f;
const float EntityFactory::block_uvy = 2.f / 11.f;
const float EntityFactory::block_uvw = 1.f / 15.f;
const float EntityFactory::block_uvh = 1.f / 11.f;


const Box EntityFactory::block_hitbox = { { -22,-32 },{ 22,28 },BoxType::body };
const Box EntityFactory::door_hitbox = { { -16,-96 },{ 16,0 },BoxType::trigger };
const Box EntityFactory::floor_hitbox = { { -650,-50 },{ 650, 0},BoxType::body };


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

EntityPtr EntityFactory::createEntity(EntityType type, glm::mat3 position)
{
	// Default parent is root node from app
	return createEntity(type, position, m_app->getSceneRoot());
}

EntityPtr EntityFactory::createEntity(EntityType type, glm::mat3 position, SceneObjectPtr parent)
{
	EntityPtr entity;
	// Select method for creating entity
	switch (type) {
	case(hero):
		entity = createHero(position, parent);
		break;
	case(block):
		entity = createBlock(position, parent);
		break;
	case(door):
		entity = createDoor(position, parent);
		break;
	case(floor):
		entity = createFloor(position, parent);
		break;
	default:
		break;
	}
	// Add entity to app's list
	m_app->getEntityList().push_back(entity);
	return entity;
}

EntityPtr EntityFactory::createHero(glm::mat3 position, SceneObjectPtr parent)
{
	EntityPtr hero = std::make_shared<Entity>();
	setEntityPosition(hero, position, parent);
	// Tag as player
	hero->addTag(Entity::player);
	// Start with idle pose uvRect
	std::pair<float, float> startFrame = HeroController::animation_frames.at(HeroController::idle);
	// Add MultiSprite with hero textures
	las::Array<TexturePtr> textures({
		m_app->getResourceManager()->getTexture(hero_sprite_filepath),
		m_app->getResourceManager()->getTexture(hero_robe_filepath),
		m_app->getResourceManager()->getTexture(hero_armour_filepath),
		m_app->getResourceManager()->getTexture(hero_helmet_filepath),
		m_app->getResourceManager()->getTexture(hero_shield_filepath) });
	hero->addComponent(std::make_shared<MultiSprite>(textures,
		hero_sprite_width, hero_sprite_height, startFrame.first, startFrame.second,
		HeroController::sprite_uv_width, HeroController::sprite_uv_height));
	// Add empty collider, as controller will set hitboxes
	hero->addComponent(std::make_shared<Collider>());
	// Add HeroController last, as it depends on other components
	hero->addComponent(std::make_shared<HeroController>());
	//TODO add a sword entity, child of the hero, to entity list after hero
	// hero has weakptr to it
	return hero;
}

EntityPtr EntityFactory::createBlock(glm::mat3 position, SceneObjectPtr parent)
{
	EntityPtr block = std::make_shared<Entity>();
	setEntityPosition(block, position, parent);
	// Tag as floor, so it can be walked on
	block->addTag(Entity::floor);
	// Add sprite
	block->addComponent(std::make_shared<Sprite>(m_app->getResourceManager()->getTexture(filepath::castle_tiles),
		block_sprite_width, block_sprite_height, block_uvx, block_uvy, block_uvw, block_uvh));
	// Add collider with body hitbox
	std::shared_ptr<Collider> collider = std::make_shared<Collider>();
	collider->setBoxes({ block_hitbox });
	block->addComponent(collider);
	return block;
}

EntityPtr EntityFactory::createDoor(glm::mat3 position, SceneObjectPtr parent)
{
	EntityPtr door = std::make_shared<Entity>();
	setEntityPosition(door, position, parent);
	// Tag as door
	door->addTag(Entity::door);
	// Add sprite 
	door->addComponent(std::make_shared<Sprite>(m_app->getResourceManager()->getTexture(filepath::castle_tiles),
		door_sprite_width, door_sprite_height, door_uvx, door_uvy, door_uvw, door_uvh));
	// Add collider with trigger hitbox
	std::shared_ptr<Collider> collider = std::make_shared<Collider>();
	collider->setBoxes({ door_hitbox });
	door->addComponent(collider);
	return door;
}

EntityPtr EntityFactory::createFloor(glm::mat3 position, SceneObjectPtr parent)
{
	EntityPtr floor = std::make_shared<Entity>();
	setEntityPosition(floor, position, parent);
	// Tag as floor
	floor->addTag(Entity::floor);
	// Add collider with long body hitbox
	std::shared_ptr<Collider> collider = std::make_shared<Collider>();
	collider->setBoxes({ floor_hitbox });
	floor->addComponent(collider);
	return floor;
}

bool EntityFactory::setEntityPosition(EntityPtr entity, glm::mat3 position, SceneObjectPtr parent)
{
	SceneObjectPtr pos = entity->getPosition();
	pos->setLocalTransform(position);
	// Add to scene graph
	return parent->addChild(pos);
}
