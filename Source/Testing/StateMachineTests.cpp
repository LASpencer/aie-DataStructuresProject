#include "stdafx_test.h"
#include "catch.hpp"
#include "StateMachine.h"
#include "State.h"
#include "Condition.h"
#include "Transition.h"

//TODO test statemachine
//TODO test statestackmachine

//HACK just to check CATCH still works
TEST_CASE("State Machine", "[state][state machine]") {
	REQUIRE(1 == 1);
	REQUIRE_FALSE(1 == 0);
}