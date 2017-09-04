#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "InputController.h"
#include <vector>


using namespace std;

class State;

class App
{
public:
	//The window to render to 
	SDL_Window* gWindow = NULL;

	//The Window renderer
	SDL_Renderer* gRenderer;

	//The input controller
	InputController* inputController=NULL;

	//Flag for the current game state
	State* currentState;
	
	//globally used font
	TTF_Font *gFont = NULL;
	//rendered texture
	//Text gTextTexture;

	App();
	
	~App();
	//initializes other devices and important flags
	bool init();
	//cleans up SDL devices and frees pointer memory (I think I need to ACTUALLY do this... haven't yet)
	void close();
	//The main gameloop / update/draw/input loop
	void gameLoop();

	void changeState(State* destState);
	void pushState(State* destState);
	void popState();

	//Calls the input/updtate/draw method of the state currently on top of the stack
	void input();
	void update();
	void draw();
	
private:

	//Flag for user quit
	bool gameRunning;

	//stack of states
	vector<State*> states;

};


