#pragma once
#include "Entity.h"
#include "Map.h"
#include "ResourceManager.h"

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
		run			//Indicates first run frame, additional frames are 0.125 away up to 0.875
	};

	static const float sprite_width;
	static const float sprite_height;
	static const float sprite_uv_width;
	static const float sprite_uv_height;

	//Sword: Up 10 across ~8 on windup, Up 10 across ~8 on strike1, up 10 across ~8 on strike2, up ~1 across ~10 on winddown
	Hero();

	Hero(TexturePtr texture);

	virtual ~Hero();

	virtual void update(float deltaTime);

	virtual void draw(aie::Renderer2D* renderer);

	static void setupFrames();
protected:
	// Map holding UVRect values for each stance
	static las::Map<Stance, std::pair<float, float>> m_animationFrames;
	
	

};