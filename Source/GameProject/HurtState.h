#pragma once
#include "HeroState.h"

class HurtState : public HeroState {
	//Move to DeadState if no health left
	//Move to GetupState after time
};

class AirHurtState : public HurtState {
	//As above but:
	//Move to GetUpState after hitting ground + time
};

class CrouchHurtState : public HurtState {
	//As HurtState, but different sprite
};