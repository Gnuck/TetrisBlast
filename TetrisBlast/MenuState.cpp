#include "MenuState.h"
#include "playState.h"


MenuState MenuState::m_MenuState;

MenuState::MenuState()
{
}


MenuState::~MenuState()
{
}

void MenuState::init() {

}

void MenuState::cleanup() {

}

void MenuState::pause() {

}

void MenuState::resume() {

}

void MenuState::handleEvents(App* app) {
	app->inputController->readInput();

	bool* keysHeld = app->inputController->getInput();
	if (keysHeld[SDL_SCANCODE_DOWN]) {
	
	}
	if (keysHeld[SDL_SCANCODE_UP]) {

	}
	if (keysHeld[SDL_SCANCODE_DOWN]) {

	}
	if (keysHeld[SDL_SCANCODE_LEFT]) {

	}
	if (keysHeld[SDL_SCANCODE_RIGHT]) {

	}
	if (keysHeld[SDL_SCANCODE_RETURN]) {
		app->pushState(playState::Instance());
		keysHeld[SDL_SCANCODE_RETURN] = false;
	}
}

void MenuState::update(App* app)
{

	
}

void MenuState::draw(App* app) {
	SDL_SetRenderDrawColor(app->gRenderer, 255, 255, 255, 0);
	SDL_RenderClear(app->gRenderer);

	//Render red filled quad
	SDL_Rect fillRect = { SCREEN_WIDTH / 4,SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	SDL_SetRenderDrawColor(app->gRenderer, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(app->gRenderer, &fillRect);

	SDL_RenderPresent(app->gRenderer);
}