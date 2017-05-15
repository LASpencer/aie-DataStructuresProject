#include "GameProjectApp.h"

int main() {
	
	// allocation
	auto app = new GameProjectApp();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	return 0;
}