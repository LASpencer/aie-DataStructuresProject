#pragma once
#include "HeroState.h"

class AttackState : public HeroState {
	//Move to IdleState after attack finished
	//Move to HurtState if damage taken
};

class AirAttackState : public AttackState {
	//Move to JumpState if attack finishes while still in air
	//Move to IdleState if attack finishes on ground
	//Move to JumpHurtState if damage taken
};

class CrouchAttackState : public AttackState {
	//Move to CrouchState after attack finished
	//Move to CrouchHurtState if damage taken
};