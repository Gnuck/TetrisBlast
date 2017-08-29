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

//void InputController::processMenuInput() {
//
//	//Event handler
//	SDL_Event e;
//
//
//	//Handle events on queue
//	while (SDL_PollEvent(&e) != 0) {
//		//USer requests quit
//		if (e.type == SDL_QUIT) {
//			pressedQuit = true;
//			App::gameRunning = false;
//		}
//		else if (e.type == SDL_KEYDOWN) {
//			switch (e.key.keysym.sym) {
//				case(SDLK_DOWN):	
//				keyPressed = KEY_PRESS_SURFACE_DOWN;
//				break;
//
//				case(SDLK_UP):
//				keyPressed = KEY_PRESS_SURFACE_UP;
//				break;
//
//				case(SDLK_LEFT):
//				keyPressed = KEY_PRESS_SURFACE_LEFT;
//				break;
//
//				case(SDLK_RIGHT):
//				keyPressed = KEY_PRESS_SURFACE_RIGHT;
//				break;
//
//				case(SDLK_RETURN):
//				App::currentState = PLAY_STATE;
//				break;
//
//				default:
//				keyPressed = KEY_PRESS_SURFACE_DEFAULT;
//				break;
//			}
//		}
//	}
//}

//void InputController::processPlayInput() {
//
//	Event handler
//	SDL_Event e;
//
//
//
//	Handle events on queue
//	while (SDL_PollEvent(&e) != 0) {
//		USer requests quit
//		if (e.type == SDL_QUIT) {
//			pressedQuit = true;
//			App::gameRunning = false;
//		}
//		else if (e.type == SDL_KEYDOWN) {
//			switch (e.key.keysym.sym) {
//			case(SDLK_DOWN):
//				keyPressed = KEY_PRESS_SURFACE_DOWN;
//				break;
//
//			case(SDLK_UP):
//				keyPressed = KEY_PRESS_SURFACE_UP;
//				break;
//
//			case(SDLK_LEFT):
//				keyPressed = KEY_PRESS_SURFACE_LEFT;
//				break;
//
//			case(SDLK_RIGHT):
//				keyPressed = KEY_PRESS_SURFACE_RIGHT;
//				break;
//
//			case(SDLK_RETURN):
//				App::currentState = MENU_STATE;
//				break;
//
//			default:
//				keyPressed = KEY_PRESS_SURFACE_DEFAULT;
//				break;
//			}
//		}
//	}
//}

void InputController::readInput() {
	while (SDL_PollEvent(&event)) {
		if (event.type == SDL_QUIT) {
			pressedQuit = true;
		}
		else if (event.type == SDL_KEYDOWN) {
			keysHeld[event.key.keysym.scancode] = true;
			down++;
			printf("keydown event registered %d \n",down);
		}
		else if (event.type == SDL_KEYUP) {
			keysHeld[event.key.keysym.scancode] = false;
		}
	}
}

bool* InputController::getInput() {
	return keysHeld;
}
