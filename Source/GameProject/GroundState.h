#pragma once
#include "HeroState.h"

class GroundState :
	public HeroState {
	//TODO check if feet touched ground last frame, if not go to FallState
	//other states derive from this, so can be partly abstract
};