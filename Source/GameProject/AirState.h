#pragma once
#include "HeroState.h"

class AirState :
	public HeroState {
	//TODO Every frame reduce verticalSpeed by some rate, and move up by vertical speed
	//If body collides from above, verticalSpeed instead set to 0
	//other states derive from this, so can be partly abstract
};