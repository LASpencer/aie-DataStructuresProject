#include "stdafx_test.h"
#include "catch.hpp"
#include "StateMachine.h"
#include "State.h"
#include "FooState.h"
#include "BarState.h"
#include "BazState.h"
#include "FooStackState.h"
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


std::shared_ptr<FooStackState> update(StateStackMachine<FooStackState>& machine) {
	const las::Stack<int>* stateStack = machine.getStateStack();
	for (size_t i = 0; i < stateStack->size(); ++i) {
		machine.getState(stateStack->peek(i))->update();
	}
	machine.updateState();
	return machine.getCurrentState();
}

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
		SECTION("Transition from any state") {
			std::shared_ptr<BazState> baz(new BazState());
			std::shared_ptr<fooValueEqualsCondition> bazReach53(new fooValueEqualsCondition(53, baz));
			baz->addTransition(std::make_shared<Transition>(bazReach53, 1));
			std::shared_ptr<fooDivisibleByCondition> anyDiv3(new fooDivisibleByCondition(3, &fooMachine));
			fooMachine.addState(3, baz);
			fooMachine.addTransition(std::make_shared<Transition>(anyDiv3, 3));
			REQUIRE_FALSE(anyDiv3->test());
			state = update(fooMachine);
			REQUIRE(state->getValue() == 2);
			state = update(fooMachine);
			REQUIRE(state->getValue() == 50);
			state = update(fooMachine);
			// Transition to self does nothing
			CHECK(anyDiv3->test());
			REQUIRE(state->getValue() == 51);
			state = update(fooMachine);
			state = update(fooMachine); 
			REQUIRE(state->getValue() == 1);
		}
	}
}

TEST_CASE("Stack State Machine", "[state][state machine][stack]") {
	StateStackMachine<FooStackState> fooMachine;
	std::shared_ptr<FooStackState> state;
	std::shared_ptr<FooStackState> foo(new FooStackState);
	std::shared_ptr<BarStackState> bar(new BarStackState);
	SECTION("Adding and checking states") {
		REQUIRE(fooMachine.addState(1, foo));
		REQUIRE(fooMachine.addState(2, bar));
		SECTION("Add state") {
			// Cannot add state with already used id
			REQUIRE_FALSE(fooMachine.addState(1, std::make_shared<BarStackState>()));
			// Can add state of same type, with new id
			REQUIRE(fooMachine.addState(3, std::make_shared<FooStackState>()));
		}
		SECTION("Force and get state") {
			REQUIRE_THROWS(fooMachine.forceState(7));
			fooMachine.forceState(1);
			REQUIRE(fooMachine.getCurrentState()->getValue() == 1);
			fooMachine.forceState(2);
			REQUIRE(fooMachine.getCurrentState()->getValue() == 100);
			fooMachine.getCurrentState()->update();
			REQUIRE(fooMachine.getCurrentState()->getValue() == 91);
		}
		SECTION("Force push and pop") {
			update(fooMachine);
			// Popping bottom does nothing
			fooMachine.forcePopState();
			REQUIRE(fooMachine.getCurrentState()->getValue() == 12);
			// Pushing same state does nothing
			fooMachine.forcePushState(1);
			REQUIRE(fooMachine.getCurrentState()->getValue() == 12);
			fooMachine.forcePushState(2);
			state = update(fooMachine);
			REQUIRE(state->getValue() == 91);
			// Lower states lose focus
			REQUIRE(fooMachine.getState(fooMachine.getStateStack()->peek(1))->getValue() == 13);
			// Popping gets lower state and gives back focus to it
			fooMachine.forcePopState();
			state = update(fooMachine);
			REQUIRE(state->getValue() == 24);
			REQUIRE(fooMachine.getStateStack()->size() == 1);
			// Pushing lower state onto stack does nothing
			fooMachine.forcePushState(2);
			fooMachine.forcePushState(1);
			REQUIRE(fooMachine.getCurrentState()->getValue() == 100);
		}
		//TODO test forcing lower state transfer when behaviour decided
	}
}