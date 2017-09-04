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
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			pressedQuit = true;
		}
		else if (event.type == SDL_KEYDOWN) {
			keysHeld[event.key.keysym.scancode] = true;
			down++;
		}
		else if (event.type == SDL_KEYUP) {
			keysHeld[event.key.keysym.scancode] = false;
		}
	}
}

bool* InputController::getInput() {
	return keysHeld;
}
