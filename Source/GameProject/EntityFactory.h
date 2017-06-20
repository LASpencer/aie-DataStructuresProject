#pragma once
#include "stdafx.h"

class Entity;
class Component;
class SceneObject;
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


	static const std::string hero_sprite_filepath;
	static const std::string hero_robe_filepath;
	static const std::string hero_armour_filepath;
	static const std::string hero_shield_filepath;
	static const std::string hero_helmet_filepath;
	static const std::string sword_sprite_filepath;

	EntityFactory(GameProjectApp* app);
	~EntityFactory();

	std::shared_ptr<Entity> createEntity(EntityType type, glm::mat3 position = glm::mat3(1));
	std::shared_ptr<Entity> createEntity(EntityType type, glm::mat3 position, std::shared_ptr<SceneObject> parent);


private:
	GameProjectApp* m_app;

	std::shared_ptr<Entity> createHero(glm::mat3 position, std::shared_ptr<SceneObject> parent);
};