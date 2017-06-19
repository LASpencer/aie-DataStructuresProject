#pragma once
#include "Controller.h"
#include "Map.h"
#include "HeroStateMachine.h"

class Box;

class HeroController :
	public Controller {
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

	static const float move_speed;
	static const float move_frame_length;
	static const float sprite_uv_width;
	static const float sprite_uv_height;

	static const las::Map<Stance, std::pair<float, float>> animation_frames;
	static const Box stand_hitbox;
	static const Box run_hitbox;
	static const Box crouch_hitbox;
	static const Box downed_hitbox;
	//TODO attack boxes


	HeroController();
	virtual ~HeroController();

	virtual void update(float deltaTime);

	virtual void draw(aie::Renderer2D* renderer);

	virtual bool onAdd(EntityPtr entity);

	void setStance(Stance stance);

protected:
	// Map holding UVRect values for each stance
	static las::Map<Stance, std::pair<float, float>> m_animationFrames;
	//TODO add sword entity (reference?)
	HeroStateMachine m_stateMachine;
};