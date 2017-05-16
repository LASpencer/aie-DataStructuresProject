// Testing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "Array.h"
#include "Stack.h"
#include <algorithm>

TEST_CASE("Integer Array", "[array][container]") {
	las::Array<int> arr;

	REQUIRE((arr.size() == 0));
	REQUIRE(arr.empty());
	REQUIRE(arr.capacity() == las::Array<int>::DEF_CAPACITY);

	SECTION("Value constructor") {
		las::Array<int> arr2(5, 2);
		REQUIRE(arr2.size() == 5);
		REQUIRE(arr2[4] == 2);
		CHECK(arr2.capacity() == std::max(las::Array<int>::DEF_CAPACITY, 8u));
	}

	SECTION("Copy Constructor") {
		arr[3] = 5;
		las::Array<int> arr2 = arr;
		REQUIRE(arr2[3] == 5);
	}

	SECTION("Initializer list") {
		arr = { 3,2,1,5,6 };
		REQUIRE(arr.size() == 5);
		REQUIRE(arr[0] == 3);
		REQUIRE(arr[2] == 1);
		REQUIRE(arr[4] == 6);
	}

	SECTION("Equality operator") {
		arr = las::Array<int>(2, 5);
		las::Array<int> arr2(3, 5);
		// Different sizes are not equal
		REQUIRE(!(arr == arr2));
		REQUIRE(arr != arr2);
		arr[2] = 5;
		// Same size and elements
		REQUIRE(arr == arr2);
		REQUIRE(!(arr != arr2));
		// Different elements are not equal
		arr[2] = 3;
		REQUIRE(arr != arr2);
		REQUIRE(!(arr == arr2));
	}

	SECTION("Subscript operator") {
		arr[3] = 5;
		REQUIRE(arr[3] == 5);
		REQUIRE(arr.size() == 4);	//Adding beyond range increases array size
		arr[2] = 9;
		REQUIRE(arr[2] == 9);
		REQUIRE(arr.size() == 4);
		arr[8] = 6;
		REQUIRE(arr[8] == 6);
		REQUIRE(arr[7] == 0);		// Extra elements have default value
		REQUIRE(arr.size() == 9);
		CHECK(arr.capacity() == 16);
	}

	//TODO const subscript operator throws out of bounds exception

	SECTION("Reserve and shrink array") {
		// Reserve less than current capacity
		arr.reserve(3);
		REQUIRE(arr.capacity() == las::Array<int>::DEF_CAPACITY);
		// Reserve increases to next power of 2
		arr.reserve(12);
		REQUIRE(arr.capacity() == 16);
		// Shrink to greater capacity does nothing
		arr.shrink_to_fit(30);
		REQUIRE(arr.capacity () == 16);
		// Shrink to smaller capacity
		arr.shrink_to_fit(3);
		REQUIRE(arr.capacity() == 4);
		// Shrink to current size
		arr.shrink_to_fit();
		REQUIRE(arr.capacity() == 2);
		arr[9] = 5;
		arr.shrink_to_fit();
		REQUIRE(arr.capacity() == 16);
	}

	SECTION("Push and Pop") {
		arr.push_back(7);
		arr.push_back(3);
		arr.push_back(8, 3);
		REQUIRE(arr[0] == 7);
		REQUIRE(arr[1] == 3);
		REQUIRE(arr[2] == 8);
		REQUIRE(arr[4] == 8);
		REQUIRE(arr.pop_back() == 8);
		REQUIRE(arr.pop_back() == 8);
		REQUIRE(arr.pop_back() == 8);
		REQUIRE(arr.pop_back() == 3);
		REQUIRE(arr.size() == 1);
		REQUIRE(arr.pop_back() == 7);
		CHECK(arr.empty());
		//TODO popping empty array throws exception
	}

	SECTION("Insert") {
		arr[0] = 1;
		arr[1] = 2;
		arr[2] = 3;
		arr[3] = 4;
		arr[4] = 5;
		arr.insert(3, 9);
		REQUIRE(arr[3] == 9);
		REQUIRE(arr[2] == 3);
		REQUIRE(arr[4] == 4);
		REQUIRE(arr.size() == 6);
		arr.insert(2, 8, 3);
		REQUIRE(arr[1] == 2);
		REQUIRE(arr[2] == 8);
		REQUIRE(arr[4] == 8);
		REQUIRE(arr[5] == 3);
		REQUIRE(arr[6] == 9);
		REQUIRE(arr[7] == 4);
		REQUIRE(arr.size() == 9);
	}

	SECTION("Erase and clear") {
		arr = { 1,2,3,4,5,6 };
		arr.erase(7);
		REQUIRE(arr == las::Array<int>({ 1, 2, 3, 4, 5, 6 }));
		arr.erase(3);
		REQUIRE(arr == las::Array<int>({1, 2, 3, 5, 6}));
		arr.clear();
		REQUIRE(arr == las::Array<int>());
	}
}

TEST_CASE("Integer Stack", "[stack][container]") {
	las::Stack<int> s;
	//TODO test cases
	SECTION("Push and Pop") {
		//Pop value from empty stack
		REQUIRE(s.pop())
	}
}


int main(int argc, char* const argv[]) {
	int result = Catch::Session().run(argc, argv);
	system("pause");
	return result;
}


