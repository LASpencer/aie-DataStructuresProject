#include "stdafx.h"
#include "GameProjectApp.h"
//HACK for test
int main() {
	
	// allocation
	auto app = new GameProjectApp();
	// initialise and loop
	app->run("Code Design and Data Structures Project - Leonard Andrew Spencer", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}