//Using SDL and standard IO
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
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

//The window we'll be render to 
SDL_Window* gWindow = NULL;

//The surface contained by the window
SDL_Surface* gScreenSurface = NULL;

//images that correspond to a keypress
SDL_Texture* gKeyPressTextures[KEY_PRESS_SURFACE_TOTAL];

//The image we will load and show on the screen
SDL_Texture* gCurrentTexture = NULL;
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
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			} 
			else {
				//Initialized renderer color

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
	gKeyPressTextures[KEY_PRESS_SURFACE_DEFAULT] = loadTexture("press.bmp");
	if (gKeyPressTextures[KEY_PRESS_SURFACE_DEFAULT] == NULL) {
		printf("Failed to load default image!\n");
		success = false;
	}
	gKeyPressTextures[KEY_PRESS_SURFACE_UP] = loadTexture("up.bmp");
	if (gKeyPressTextures[KEY_PRESS_SURFACE_UP] == NULL) {
		printf("Failed to load up image!\n");
		success = false;
	}
	gKeyPressTextures[KEY_PRESS_SURFACE_DOWN] = loadTexture("down.bmp");
	if (gKeyPressTextures[KEY_PRESS_SURFACE_DOWN] == NULL) {
		printf("Failed to load down image!\n");
		success = false;
	}
	gKeyPressTextures[KEY_PRESS_SURFACE_LEFT] = loadTexture("left.bmp");
	if (gKeyPressTextures[KEY_PRESS_SURFACE_LEFT] == NULL) {
		printf("Failed to load left image!\n");
		success = false;
	}
	gKeyPressTextures[KEY_PRESS_SURFACE_RIGHT] = loadTexture("texture.png");
	if (gKeyPressTextures[KEY_PRESS_SURFACE_RIGHT] == NULL) {
		printf("Failed to load right image!\n");
		success = false;
	}
	return success;
}

SDL_Texture* loadTexture(std::string path) {

	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL){
		printf("Unable to load image %s. SDL Error %s\n", path.c_str(), SDL_GetError());
	}
	else {
		//Create texture form surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL) {
			printf("Unable to optimize image %s! SDL Error: %s\n", path, SDL_GetError());
		}
		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}

void close() {
	//free loaded images
	for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
	{
		SDL_DestroyTexture(gKeyPressTextures[i]);
		gKeyPressTextures[i] = NULL;
	}
	SDL_DestroyTexture(gCurrentTexture);
	//Destory window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
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
			gCurrentTexture = gKeyPressTextures[KEY_PRESS_SURFACE_DEFAULT];
			while (gameRunning) {

				//Handle inputs
				inputController->processInput();
				gCurrentTexture = gKeyPressTextures[inputController->pressedKey()];
				if (inputController->hasQuit()) {
					gameRunning = false;
				}

				//update scene
			
				//Clear screen
				SDL_SetRenderDrawColor(gRenderer, 255, 255, 255, 0);
				SDL_RenderClear(gRenderer);
				
				//Render red filled quad
				SDL_Rect fillRect = { SCREEN_WIDTH / 4,SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
				SDL_RenderFillRect(gRenderer, &fillRect);

				SDL_Rect outlineRect = { SCREEN_WIDTH / 6,SCREEN_HEIGHT / 6, SCREEN_WIDTH *2/3, SCREEN_HEIGHT *2/3 };
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
				SDL_RenderDrawRect(gRenderer, &outlineRect);

				//Draw blue horizontal line
				SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
				SDL_RenderDrawLine(gRenderer, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

				//Draw vertical line of yellow dots
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
				for (int i = 0; i < SCREEN_HEIGHT; i += 4) {
					SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, i);
				}

				//Render texture to the screen
				//SDL_RenderCopy(gRenderer, gCurrentTexture, NULL, NULL);
				
				//Update screen
				SDL_RenderPresent(gRenderer);
			}

		}
	}
	close();

	return 0;
}

