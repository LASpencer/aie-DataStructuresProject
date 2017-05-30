#include "stdafx_test.h"
#include "catch.hpp"
#include "ResourceManager.h"
#include "Texture.h"


TEST_CASE("Resource Manager") {
	ResourceManager<aie::Texture> textureManager;
	ResourceManager<aie::Texture>::ResourcePtr sprite;

	SECTION("Adding resources") {
		REQUIRE(textureManager.size() == 0);
		textureManager.get("./textures/car.png");
		REQUIRE(textureManager.size() == 1);
		textureManager.get("./textures/ship.png");
		REQUIRE(textureManager.size() == 2);
		textureManager.get("./textures/car.png");
		REQUIRE(textureManager.size() == 2);
		sprite = textureManager.get("./textures/ship.png");
		REQUIRE((*sprite)->getHeight() == 80);
	}
	SECTION("Garbage collection") {
		textureManager.get("./textures/car.png");
		textureManager.get("./textures/ship.png");
		textureManager.get("./textures/grass.png");
		REQUIRE(textureManager.size() == 3);
		SECTION("Collect all garbage") {
			textureManager.collectGarbage();
			REQUIRE(textureManager.size() == 0);
		}
		SECTION("Don't collect resource in use") {
			sprite = textureManager.get("./textures/ship.png");
			CHECK(textureManager.size() == 3);
			textureManager.collectGarbage();
			REQUIRE(textureManager.size() == 1);
			REQUIRE((*sprite)->getHeight() == 80);
		}
	}
}