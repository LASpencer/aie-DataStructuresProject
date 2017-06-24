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

	HeroController acts as a proxy observer for the current state. Rather
	than having all states be notified of an event, whether or not they're 
	active, this subscribes to the subject instead and passes on events to
	the current state. This both avoids unintentional behaviour from inactive
	states, and reduces the number of observers the subject needs to store and
	notify.

	Requires Collider and Sprite components, and for the entity
	to be tagged as player
	*/
class HeroController :
	public Controller, public Observer {
public:

	// Enumeration of every pose the hero can make
	enum Pose {
		idle,
		crouch,
		jump,
		falling,
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
		knockback,
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
	static const float air_lateral_speed;		// Lateral distance speed when in air
	static const float fall_rate;				// Downward acceleration when in air
	static const float jump_speed;				// Vertical speed at start of jump

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

	/** Sets sprite uvRect and collider hitboxes to match new pose
	*	@param pose new pose for hero entity*/
	void setPose(Pose pose);

	// Returns true unconditionally
	virtual bool addSubject(Subject* subject);
	// Does nothing
	virtual void removeSubject(Subject* subject);
	// Passes notification on to current state
	virtual void notify(Subject* subject, EventBase* event);

	/** Tests whether entity is valid for this component
	*	@param entity Entity being checked
	*	@return true if entity is valid*/
	virtual bool isValidEntity(EntityPtr entity);
	
	void setVerticalSpeed(float speed);

	float getVerticalSpeed();

protected:
	// Map holding UVRect values for each stance
	static las::Map<Pose, std::pair<float, float>> m_animationFrames;
	
	float m_verticalSpeed;
	//TODO add sword entity (reference?)
	HeroStateMachine m_stateMachine;

};