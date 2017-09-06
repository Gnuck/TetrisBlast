//Using SDL and standard IO
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include "InputController.h"
#include <string>
#include "Constants.h"
#include "MenuState.h"
#include "app.h"



//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Loads invidiviual image
SDL_Surface* loadSurface(std::string path);

//Loads individual image as texture 
SDL_Texture* loadTexture(std::string path);

//The Window renderer
SDL_Renderer* gRenderer = NULL;

//The window we'll be render to 
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//The image we will load and show on the screen
SDL_Texture* gCurrentTexture = NULL;
SDL_Surface* gStretchedSurface = NULL;

InputController* inputController = NULL;






int main(int argc, char*args[]){

	App app;

	//Start up SDL and create window
	if(!app.init()){
		printf("Failed to initialize! \n");
	}
	else {
		app.changeState(MenuState::Instance());
		app.gameLoop();
	}
	app.close();

	return 0;
}

