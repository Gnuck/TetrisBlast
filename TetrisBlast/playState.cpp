#include "playState.h"


playState playState::m_playState;

playState::playState()
{
}


playState::~playState()
{
}

void playState::init() {
	tetronimo = new Tetronimo((LEFT_WALL+RIGHT_WALL)/2, CEILING);
	board = new Board();
}

void playState::cleanup() {

}

void playState::handleEvents(App* app) {
	app->inputController->readInput();

	bool* keysHeld = app->inputController->getInput();

	if (keysHeld[SDL_SCANCODE_UP]) {
		tetronimo->rotateCCW();
		if (tetronimo->belowCollisions(board->boardBlocks)) {
			tetronimo->rotateCW();
		}
		keysHeld[SDL_SCANCODE_UP] = false;
	}
	if (keysHeld[SDL_SCANCODE_DOWN]) {
		tetronimo->moveDown();
		if (tetronimo->belowCollisions(board->boardBlocks)) {
			tetronimo->moveUp();
			board->addBlocksToBoard(tetronimo);
			//delete tetronimo here?
			tetronimo->~Tetronimo();
			////////////////////////

			generateTetronimo();
			//tetronimo->moveUp();
			//add tetronimo to board state
		}
		keysHeld[SDL_SCANCODE_DOWN] = false;
	}
	if (keysHeld[SDL_SCANCODE_LEFT]) {
		tetronimo->moveLeft();
		//if this move made the block move past the wall, undo the past move
		if (tetronimo->HorizCollision(board->boardBlocks)) {
			tetronimo->moveRight();
		}
		keysHeld[SDL_SCANCODE_LEFT] = false;
	}
	if (keysHeld[SDL_SCANCODE_RIGHT]) {
		tetronimo->moveRight();
		//if this move made the block move past the wall, undo the past move
		if (tetronimo->HorizCollision(board->boardBlocks)) {
			tetronimo->moveLeft();
		}
		keysHeld[SDL_SCANCODE_RIGHT] = false;
	}
	if (keysHeld[SDL_SCANCODE_RETURN]) {
		app->popState();
		keysHeld[SDL_SCANCODE_RETURN] = false;
	}

}
void playState::update(App* app) {

}

void playState::draw(App* app) {
	//draw background color
	SDL_SetRenderDrawColor(app->gRenderer, 0, 0, 0, 0);
	SDL_RenderClear(app->gRenderer);

	//draw board borders and grid
	board->drawBoardBorders(app->gRenderer);
	board->drawBoardGrid(app->gRenderer);

	//draw currenlty controlled tetronimo
	tetronimo->drawTetronimo(app->gRenderer);

	//Draw board blocks
	board->drawBoardBlocks(app->gRenderer);

	SDL_RenderPresent(app->gRenderer);
}

void playState::pause() {

}

void playState::resume() {

}

void playState::generateTetronimo() {
	tetronimo = new Tetronimo((LEFT_WALL + RIGHT_WALL) / 2, CEILING);
}
