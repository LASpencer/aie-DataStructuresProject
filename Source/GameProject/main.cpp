#include "stdafx.h"
#include "GameProjectApp.h"
//HACK for test
#include "Hero.h"
int main() {
	
	// allocation
	auto app = new GameProjectApp();
	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}