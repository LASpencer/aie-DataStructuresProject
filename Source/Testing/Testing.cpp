// Testing.cpp : Defines the entry point for the console application.
//
#pragma once
#define CATCH_CONFIG_RUNNER
#include "stdafx.h"

int main(int argc, char* const argv[]) {
	int result = Catch::Session().run(argc, argv);
	system("pause");
	return result;
}


