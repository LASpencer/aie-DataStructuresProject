// Testing.cpp : Defines the entry point for the console application.
//
#include "stdafx_test.h"
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"

int main(int argc, char* const argv[]) {
	int result = Catch::Session().run(argc, argv);
	system("pause");
	return result;
}


