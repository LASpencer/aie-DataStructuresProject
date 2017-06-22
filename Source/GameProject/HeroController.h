#pragma once
#include "Controller.h"
#include "Map.h"
#include "HeroStateMachine.h"
#include "Observer.h"

class Box;

/*	Component to control the entity for the player's character
	Contains a HeroStateMachine to determine behaviour based on
	current state, and methods to set the animation frames and hitboxes
	to different poses.
	Requires Sprite and Collider components
	*/
class HeroController :
	public Controller, public Observer {
public:

	// Enumeration of every pose the hero can make
	enum Pose {
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

	static const float move_speed;				// Distance per second moved when running
	static const float move_frame_length;		// Time in seconds to show each run pose
	static const float sprite_uv_width;	
	static const float sprite_uv_height;

	// uvRect positions for each pose
	static const las::Map<Pose, std::pair<float, float>> animation_frames;
	
	// Body box for various poses
	static const Box stand_hitbox;
	static const Box run_hitbox;
	static const Box crouch_hitbox;
	static const Box downed_hitbox;

	// Feet box for various poses
	static const Box stand_feetbox;
	static const Box run_feetbox;
	static const Box crouch_feetbox;
	static const Box downed_feetbox;
	//TODO attack boxes

	HeroController();
	virtual ~HeroController();

	virtual void update(float deltaTime);
	virtual void draw(aie::Renderer2D* renderer);

	virtual bool onAdd(EntityPtr entity);
	virtual void onRemove(EntityPtr entity);

	void setPose(Pose stance);

	virtual bool addSubject(Subject* subject);
	virtual void removeSubject(Subject* subject);
	virtual void notify(Subject* subject, EventBase* event);

protected:
	// Map holding UVRect values for each stance
	static las::Map<Pose, std::pair<float, float>> m_animationFrames;
	//TODO add sword entity (reference?)
	HeroStateMachine m_stateMachine;
};