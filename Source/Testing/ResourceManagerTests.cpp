#include "stdafx_test.h"
#include "catch.hpp"
#include "ResourceManager.h"
#include "Texture.h"
//TODO rewrite after refactoring REsourceManager

TEST_CASE("Resource Manager") {
	ResourceManager resourceManager;
	SECTION("Textures") {
		TexturePtr sprite;
		SECTION("Adding resources") {
			REQUIRE(resourceManager.size(ResourceManager::ResourceType::texture) == 0);
			resourceManager.getTexture("./textures/car.png");
			REQUIRE(resourceManager.size(ResourceManager::texture) == 1);
			resourceManager.getTexture("./textures/ship.png");
			REQUIRE(resourceManager.size(ResourceManager::texture) == 2);
			resourceManager.getTexture("./textures/car.png");
			REQUIRE(resourceManager.size(ResourceManager::texture) == 2);
			sprite = resourceManager.getTexture("./textures/ship.png");
			REQUIRE((*sprite)->getHeight() == 80);
		}
		SECTION("Garbage collection") {
			resourceManager.getTexture("./textures/car.png");
			resourceManager.getTexture("./textures/ship.png");
			resourceManager.getTexture("./textures/grass.png");
			REQUIRE(resourceManager.size(ResourceManager::texture) == 3);
			SECTION("Collect all garbage") {
				resourceManager.collectGarbage();
				REQUIRE(resourceManager.size(ResourceManager::texture) == 0);
			}
			SECTION("Don't collect resource in use") {
				sprite = resourceManager.getTexture("./textures/ship.png");
				CHECK(resourceManager.size(ResourceManager::texture) == 3);
				resourceManager.collectGarbage();
				REQUIRE(resourceManager.size(ResourceManager::texture) == 1);
				REQUIRE((*sprite)->getHeight() == 80);
			}
		}
	}
}