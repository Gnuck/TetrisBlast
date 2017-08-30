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
	//tetronimo = new Block(fillRect);
	tetronimo = new Tetronimo(33, 33);
	board = new Board();
}

void playState::cleanup() {

}

void playState::handleEvents(App* app) {
	app->inputController->readInput();

	bool* keysHeld = app->inputController->getInput();

	if (keysHeld[SDL_SCANCODE_UP]) {
		tetronimo->rotate();
		keysHeld[SDL_SCANCODE_UP] = false;
	}
	if (keysHeld[SDL_SCANCODE_DOWN]) {
		tetronimo->moveDown();
		keysHeld[SDL_SCANCODE_DOWN] = false;
	}
	if (keysHeld[SDL_SCANCODE_LEFT]) {
		tetronimo->moveLeft();
		keysHeld[SDL_SCANCODE_LEFT] = false;
	}
	if (keysHeld[SDL_SCANCODE_RIGHT]) {
		tetronimo->moveRight();
		keysHeld[SDL_SCANCODE_RIGHT] = false;
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
	tetronimo->drawTetronimo(app->gRenderer);
	SDL_RenderPresent(app->gRenderer);
}

void playState::pause() {

}

void playState::resume() {

}