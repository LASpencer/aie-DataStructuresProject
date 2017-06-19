#pragma once
#include "Entity.h"
#include "Map.h"
#include "ResourceManager.h"
#include "HeroStateMachine.h"

//TODO extract out common functionality between this and creatures into superclass

class Hero : public Entity {
public:
	enum Stance {
		idle,
		crouch,
		jump,
		land,
		wind_up,
		strike_1,
		strike_2,
		wind_down,
		hurt,
		crouch_wind_up,
		crouch_strike_1,
		crouch_strike_2,
		crouch_wind_down,
		crouch_hurt,
		jump_wind_up,
		jump_strike_1,
		jump_strike_2,
		jump_wind_down,
		falling,
		downed,
		run1,
		run2,
		run3,
		run4,
		run5,
		run6,
		run7,
		run8
	};

	static const float sprite_width;
	static const float sprite_height;
	static const float sprite_uv_width;
	static const float sprite_uv_height;

	static const float move_speed;
	static const float move_frame_length;

	static const std::string sprite_filepath;
	static const std::string robe_filepath;
	static const std::string armour_filepath;
	static const std::string shield_filepath;
	static const std::string helmet_filepath;
	static const std::string sword_filepath;

	//Sword: Up 10 across ~8 on windup, Up 10 across ~8 on strike1, up 10 across ~8 on strike2, up ~1 across ~10 on winddown
	Hero();

	Hero(las::Array<TexturePtr>& textures);

	virtual ~Hero();

	virtual void update(float deltaTime);

	virtual void draw(aie::Renderer2D* renderer);

	static void setupFrames();

	void setStance(Stance stance);

protected:
	// Map holding UVRect values for each stance
	static las::Map<Stance, std::pair<float, float>> m_animationFrames;
	//TODO add sword entity (reference?)
	HeroStateMachine m_stateMachine;

};