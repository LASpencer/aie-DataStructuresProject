#pragma once
#include "stdafx.h"

class Entity;
typedef std::shared_ptr<Entity> EntityPtr;
typedef std::weak_ptr<Entity>	EntityWeakPtr;

class Component;
typedef std::shared_ptr<Entity> EntityPtr;
typedef std::weak_ptr<Entity>	EntityWeakPtr;

class SceneObject;
typedef std::shared_ptr<SceneObject> SceneObjectPtr;
typedef std::weak_ptr<SceneObject> SceneObjectWeakPtr;

struct Box;

class GameProjectApp;

class EntityFactory {
public:
	enum EntityType {
		hero,
		block,
		floor,
		door
	};
	static const float hero_sprite_width;
	static const float hero_sprite_height;

	static const float block_sprite_width;
	static const float block_spright_height;

	static const float door_sprite_width;
	static const float door_sprite_height;
	
	static const Box	block_hitbox;
	static const Box	door_hitbox;
	static const Box	floor_hitbox;

	static const float door_uvx;
	static const float door_uvy;
	static const float door_uvw;
	static const float door_uvh;

	static const std::string hero_sprite_filepath;
	static const std::string hero_robe_filepath;
	static const std::string hero_armour_filepath;
	static const std::string hero_shield_filepath;
	static const std::string hero_helmet_filepath;
	static const std::string sword_sprite_filepath;
	static const std::string block_sprite_filepath;


	EntityFactory(GameProjectApp* app);
	~EntityFactory();

	EntityPtr createEntity(EntityType type, glm::mat3 position = glm::mat3(1));
	EntityPtr createEntity(EntityType type, glm::mat3 position, SceneObjectPtr parent);


private:
	GameProjectApp* m_app;

	EntityPtr createHero(glm::mat3 position, SceneObjectPtr parent);
	EntityPtr createBlock(glm::mat3 position, SceneObjectPtr parent);
	EntityPtr createDoor(glm::mat3 position, SceneObjectPtr parent);
	bool setEntityPosition(EntityPtr entity, glm::mat3 position, SceneObjectPtr parent);
};