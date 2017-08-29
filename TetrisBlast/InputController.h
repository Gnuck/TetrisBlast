#pragma once
#ifndef InputController_h
#define InputController_h

#include "Constants.h"
#include "SDL.h"

class InputController{

public:

	InputController();
	~InputController();


	//call this before any other methods
	void readInput();

	bool* getInput();

	bool pressedQuit = false;

	int down = 0;
	

private:
	SDL_Event event;
	bool keysHeld[323];
	

};

#endif