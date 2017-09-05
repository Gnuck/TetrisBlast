#include "InputController.h"
#include "App.h"


class App;
InputController::InputController()
{
	SDL_PumpEvents();
	for (int i = 0; i < 323; i++) {
		keysHeld[i] = false;
	}
}


InputController::~InputController()
{
}


void InputController::readInput() {
	//SDL_PumpEvents();
	while(SDL_PollEvent(&event)) {
		switch (event.type) {
		case(SDL_QUIT):
			pressedQuit = true;
			break;
		case(SDL_KEYDOWN):
			keysHeld[event.key.keysym.scancode] = true;
			break;
		case(SDL_KEYUP):
			keysHeld[event.key.keysym.scancode] = false;
			break;
		default:
			break;
		}
	}
}

bool* InputController::getInput() {
	return keysHeld;
}
