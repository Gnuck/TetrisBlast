//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include "InputController.h"
#include <string>
#include "Constants.h"

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

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

//Current displayed texture
SDL_Texture* gTexture = NULL;

//The window we'll be render to 
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//images that correspond to a keypress
SDL_Surface* gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL];

//The image we will load and show on the screen
SDL_Surface* gCurrentSurface = NULL;
SDL_Surface* pizza = NULL;
SDL_Surface* gStretchedSurface = NULL;

InputController* inputController = NULL;

//Flag for user quit
bool gameRunning = true;

bool init() {
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		//Create Window
		gWindow = SDL_CreateWindow("Tetris Blast", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created. SDL_Error: %s\n", SDL_GetError());
			success = false;
		}
		else{
			//create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL) {
				printf("Renderer coudl not be created! SDL Error: %s\n", SDL_GetError());
			} 
			else {
				//Initialized renderer color
				SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 255);
				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags)) {
					printf("SDL_image could not initailize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				else {
					//Get window surface
					gScreenSurface = SDL_GetWindowSurface(gWindow);
				}
			}


		}
	}
	//Create input controller
	inputController = new InputController();
	return success;
}


bool loadMedia() {
	//Loading success flag
	bool success = true;

	//Load default surface
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("press.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
		printf("Failed to load default image!\n");
	}
	gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("up.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == NULL) {
		printf("Failed to load up image!\n");
	}
	gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("down.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == NULL) {
		printf("Failed to load down image!\n");
	}
	gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("left.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == NULL) {
		printf("Failed to load left image!\n");
	}
	gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("right.bmp");
	if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == NULL) {
		printf("Failed to load right image!\n");
	}
	//Load splash image
	pizza = loadSurface("pizza.bmp");
	if (pizza == NULL) {
		printf("Failed to load pizza\n");
	}
	return success;
}

SDL_Surface* loadSurface(std::string path) {

	//The final optimized image
	SDL_Surface* optimizedSurface = NULL;
	SDL_Surface* loadedSurface = NULL;

	//Load image at specified path

	loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL){
		printf("Unable to load image %s. SDL Error %s\n", path.c_str(), SDL_GetError());
	}
	else {
		//Convert surface to screen format
		optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, NULL);
		if (optimizedSurface == NULL) {
			printf("Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError());
		}
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return optimizedSurface;
}


void close() {
	//Deallocate surface
	SDL_FreeSurface(gCurrentSurface);
	SDL_FreeSurface(pizza);
	gCurrentSurface = NULL;
	//Destory window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	//Quit SDL subsystems
	SDL_Quit();

}

int main(int argc, char*args[]){
	//Start up SDL and create window
	if(!init()){
		printf("Failed to initialize! \n");
	}
	else {
		//Load media
		if (!loadMedia()) {
			printf("Failed to load media!\n");
		}
		else {
			//Apply the image
			gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
			while (gameRunning) {

				//Handle inputs
				inputController->processInput();
				gCurrentSurface = gKeyPressSurfaces[inputController->pressedKey()];
				if (inputController->hasQuit()) {
					gameRunning = false;
				}

				//update scene
				SDL_BlitSurface(gCurrentSurface, NULL, gScreenSurface, NULL);
				SDL_Rect stretchRect;
				stretchRect.x = 0;
				stretchRect.y = 0;
				stretchRect.w = SCREEN_WIDTH;
				stretchRect.h = SCREEN_HEIGHT;
				//SDL_BlitScaled(pizza, NULL, gScreenSurface, &stretchRect);
				//SDL_BlitSurface(pizza, NULL, gScreenSurface, NULL);
				SDL_UpdateWindowSurface(gWindow);
			}

		}
	}
	close();

	return 0;
}

