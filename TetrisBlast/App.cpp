#include "App.h"
#include "MenuState.h"
#include "playState.h"
#include "Constants.h"
#include <ctime>

App::App()
{
}


App::~App()
{
}

bool App::init() {
	//Initialization flag
	bool success = true;
	srand(time(NULL));
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
		else {
			//create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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

	//Initialize input controller, set "gamerunning" flag
	gameRunning = true;
	inputController = new InputController();

	return success;
}


void App::close() {

	//Cleanup state stack
	while (!states.empty()) {
		states.back()->cleanup();
		states.pop_back();
	}
	//Destory window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

}

void App::gameLoop() {
	while (!inputController->pressedQuit) {
		input();
		update();
		draw();
	}
}

void App::changeState(State* destState) {
	//cleanup current state
	if (!states.empty()) {
		states.back()->cleanup();
		states.pop_back();
	}

	states.push_back(destState);
	states.back()->init();
}

void App::pushState(State* destState) {
	if (!states.empty()) {
		states.back()->pause();
	}

	//add new state to top of stack, init that state
	states.push_back(destState);
	states.back()->init();
}

void App::popState() {
	if (!states.empty()) {
		states.back()->cleanup();
		states.pop_back();
	}

	if (!states.empty()) {
		states.back()->resume();
	}
}

void App::input() {
	states.back()->handleEvents(this);
}

void App::update() {
	states.back()->update(this);
}

void App::draw() {
	states.back()->draw(this);
}