#pragma once
#include "Entity.h"
#include "Map.h"
#include "ResourceManager.h"
#include "HeroStateMachine.h"

//TODO extract out into a "HeroController" class, inheriting from Controller component
//Hero should just be an entity with appropriate components, 
//made by factory
//
//class Hero : public Entity {
//public:
//	
//
//	static const float sprite_width;
//	static const float sprite_height;
//	static const float sprite_uv_width;
//	static const float sprite_uv_height;
//
//	static const float move_speed;
//	static const float move_frame_length;
//
//	static const std::string sprite_filepath;
//	static const std::string robe_filepath;
//	static const std::string armour_filepath;
//	static const std::string shield_filepath;
//	static const std::string helmet_filepath;
//	static const std::string sword_filepath;
//
//	//Sword: Up 10 across ~8 on windup, Up 10 across ~8 on strike1, up 10 across ~8 on strike2, up ~1 across ~10 on winddown
//	Hero();
//
//	Hero(las::Array<TexturePtr>& textures);
//
//	virtual ~Hero();
//
//	virtual void update(float deltaTime);
//
//	virtual void draw(aie::Renderer2D* renderer);
//
//	static void setupFrames();
//
//	void setStance(Stance stance);
//
//
//
//};