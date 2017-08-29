#include "playState.h"


playState playState::m_playState;

playState::playState()
{
}


playState::~playState()
{
}

void playState::init() {
	SDL_Rect fillRect = { 33,33, 32, 32 };
	tetronimo = new Block(fillRect);
	board = new Board();
}

void playState::cleanup() {

}

void playState::handleEvents(App* app) {
	app->inputController->readInput();

	bool* keysHeld = app->inputController->getInput();

	if (keysHeld[SDL_SCANCODE_UP]) {
		tetronimo->moveVert(-32);
	}
	if (keysHeld[SDL_SCANCODE_DOWN]) {
		tetronimo->moveVert(32);
	}
	if (keysHeld[SDL_SCANCODE_LEFT]) {
		tetronimo->moveHoriz(-32);
	}
	if (keysHeld[SDL_SCANCODE_RIGHT]) {
		tetronimo->moveHoriz(32);
	}
	if (keysHeld[SDL_SCANCODE_RETURN]) {
		//app->pushState(playState::Instance());
		app->popState();
		keysHeld[SDL_SCANCODE_RETURN] = false;
	}

}
void playState::update(App* app) {

}

void playState::draw(App* app) {
	SDL_SetRenderDrawColor(app->gRenderer, 0, 0, 0, 0);
	SDL_RenderClear(app->gRenderer);




	board->drawBoardBorders(app->gRenderer);
	board->drawBoardGrid(app->gRenderer);

	//Render red filled quad
	//SDL_Rect fillRect = { 16,16, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	SDL_SetRenderDrawColor(app->gRenderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderFillRect(app->gRenderer, &(tetronimo->rect));
	SDL_RenderPresent(app->gRenderer);
}

void playState::pause() {

}

void playState::resume() {

}