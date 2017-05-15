// Testing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "Array.h"
#include <algorithm>

TEST_CASE("Integer Array", "[array][container]") {
	las::Array<int> arr;

	REQUIRE((arr.size() == 0));
	REQUIRE(arr.capacity() == las::Array<int>::DEF_SIZE);

	SECTION("Value constructor") {
		las::Array<int> arr2(5, 2);
		REQUIRE(arr2.size() == 5);
		REQUIRE(arr2[4] == 2);
		CHECK(arr2.capacity() == std::max(las::Array<int>::DEF_SIZE, 8u));
	}
	SECTION("Subscript operator") {
		arr[3] = 5;
		REQUIRE(arr[3] == 5);
		REQUIRE(arr.size() == 4);
		arr[2] = 9;
		REQUIRE(arr[2] == 9);
		REQUIRE(arr.size() == 4);
		arr[8] = 6;
		REQUIRE(arr[8] == 6);
		REQUIRE(arr.size() == 9);
		CHECK(arr.capacity() == 16);
	}

	SECTION("Reserve and shrink array") {
		arr.reserve(3);
		REQUIRE(arr.capacity() == las::Array<int>::DEF_SIZE);
		arr.reserve(12);
		REQUIRE(arr.capacity() == 16);
		arr.shrink_to_fit(30);
		REQUIRE(arr.capacity () == 16);
		arr.shrink_to_fit(3);
		REQUIRE(arr.capacity() == 4);
		arr.shrink_to_fit();
		REQUIRE(arr.capacity() == 2);
	}

}



int main(int argc, char* const argv[]) {
	int result = Catch::Session().run(argc, argv);
	system("pause");
	return result;
}


