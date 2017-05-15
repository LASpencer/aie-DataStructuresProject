// Testing.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "Array.h"

TEST_CASE("Integer Array can be created", "[array][container]") {
	las::Array<int> arr;

	REQUIRE((arr.size() == 0));
	REQUIRE(arr.capacity() == 8);		//HACK replace magic number

	//TODO value constructor
}



int main(int argc, char* const argv[]) {
	int result = Catch::Session().run(argc, argv);
	system("pause");
	return result;
}


