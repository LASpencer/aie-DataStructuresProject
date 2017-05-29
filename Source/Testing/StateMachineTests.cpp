#include "stdafx_test.h"
#include "catch.hpp"
#include "StateMachine.h"
#include "State.h"
#include "FooState.h"
#include "BarState.h"
#include "BazState.h"
#include "Condition.h"
#include "fooValueEqualsCondition.h"
#include "Transition.h"

//TODO test statemachine
//TODO test statestackmachine

std::shared_ptr<FooState> update(StateMachine<FooState>& machine) {
	machine.getState()->update();
	machine.updateState();
	return machine.getState();
}

//HACK just to check CATCH still works
TEST_CASE("State Machine", "[state][state machine]") {
	StateMachine<FooState> fooMachine;
	std::shared_ptr<FooState> state;
	SECTION("Adding and checking states"){
		REQUIRE(fooMachine.addState(1, std::make_shared<FooState>()));
		REQUIRE(fooMachine.addState(2, std::make_shared<BarState>()));

		SECTION("Add state") {
			// Cannot add state with already used id
			REQUIRE_FALSE(fooMachine.addState(1, std::make_shared<BarState>()));
			// Can add state of same type, with new id
			REQUIRE(fooMachine.addState(3, std::make_shared<FooState>()));
		}

		SECTION("Force and get state") {
			// No state returns nullptr
			REQUIRE_THROWS(fooMachine.forceState(7));
			fooMachine.forceState(1);
			REQUIRE(fooMachine.getState()->getValue() == 1);
			fooMachine.forceState(2);
			REQUIRE(fooMachine.getState()->getValue() == 10);
			update(fooMachine);
			REQUIRE(fooMachine.getState()->getValue() == 9);
			// Force move to same state does nothing
			fooMachine.forceState(2);
			REQUIRE(fooMachine.getState()->getValue() == 9);
		}
	}
	SECTION("Conditional transitions") {
		std::shared_ptr<FooState> foo(new FooState);
		std::shared_ptr<BarState> bar(new BarState);
		std::shared_ptr<fooValueEqualsCondition> fooReach5(new fooValueEqualsCondition(5, foo));
		std::shared_ptr<fooValueEqualsCondition> barReach7(new fooValueEqualsCondition(7, bar));
		foo->addTransition(std::make_shared<Transition>(fooReach5, 2));
		bar->addTransition(std::make_shared<Transition>(barReach7, 1));
		fooMachine.addState(1, foo);
		fooMachine.addState(2, bar);
		SECTION("State transitions") {
			state = update(fooMachine);
			REQUIRE(state->getValue() == 2);
			REQUIRE_FALSE(fooReach5->test());
			state = update(fooMachine);
			state = update(fooMachine);
			SECTION("Check condition evaluates to true") {
				fooMachine.getState()->update();
				REQUIRE(fooMachine.getState()->getValue() == 5);
				REQUIRE(fooReach5->test());
			}
			SECTION("Check transition occurs") {
				state = update(fooMachine);
				// Transition to Bar state
				REQUIRE(state->getValue() == 10);
				// Check exit was called
				REQUIRE(foo->getValue() == 0);
				state = update(fooMachine);
				REQUIRE(state->getValue() == 9);
				REQUIRE_FALSE(barReach7->test());
				state = update(fooMachine);
				state = update(fooMachine);
				// Transition back to Foo state
				REQUIRE(state->getValue() == 1);
			}
		}
		//SECTION("Transition from any state") {
		//	std::shared_ptr<BazState> baz(new BazState);
		//	std::shared_ptr<fooDivisibleByCondition> anyDiv3(new fooDivisibleByCondition())
		//}
	}
}