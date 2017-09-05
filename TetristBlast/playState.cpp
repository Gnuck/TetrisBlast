#include "playState.h"


playState playState::m_playState;

playState::playState()
{
}


playState::~playState()
{
}

void playState::init() {
	tetronimo = new Tetronimo((LEFT_WALL+RIGHT_WALL)/2, CEILING+BLOCK_SIZE);
	
	nextTetro = new Tetronimo((RIGHT_WALL + SCREEN_WIDTH) / 2 - 0.5*BLOCK_SIZE, CEILING + 3 * BLOCK_SIZE);
	correctNextTetroPos();

	board = new Board();
	collisionDetector = new CollisionDetector();
	timer.start();

	//resetInfo.init("r =;
	// quitInfo;
	pauseInfo;
	scoreDisplay.init("Score = " + std::to_string(score),WHITE, (RIGHT_WALL + SCREEN_WIDTH) / 2, SCREEN_HEIGHT/2,14);

	nextTetroInfo.init("Next Tetronimo", WHITE, (RIGHT_WALL + SCREEN_WIDTH) / 2,nextRect.y+nextRect.h+(int)(BLOCK_SIZE/2) , 14);

}

void playState::cleanup() {

}

void playState::handleEvents(App* app) {
	app->inputController->readInput();
	keysHeld = app->inputController->getInput();
	if (keysHeld[SDL_SCANCODE_UP]) {
		tetronimo->movement = ROTATE;
		keysHeld[SDL_SCANCODE_UP] = false;
	}
	if (keysHeld[SDL_SCANCODE_DOWN]) {
		tetronimo->movement = DOWN;
		keysHeld[SDL_SCANCODE_DOWN] = false;
	}
	if (keysHeld[SDL_SCANCODE_LEFT]) {
		tetronimo->movement = LEFT;
		keysHeld[SDL_SCANCODE_LEFT] = false;
	}
	if (keysHeld[SDL_SCANCODE_RIGHT]) {
		tetronimo->movement = RIGHT;
		keysHeld[SDL_SCANCODE_RIGHT] = false;
	}
	if (keysHeld[SDL_SCANCODE_RETURN]) {
		app->popState();
		keysHeld[SDL_SCANCODE_RETURN] = false;
	}
}

void playState::update(App* app) {
	if (!gameOver) {
		if (timer.getTime() >1000) {
			tetronimo->moveDown();
			if (collisionDetector->belowCollisions(tetronimo, board->boardBlocks)) {
				tetronimo->moveUp();
				board->addBlocksToBoard(tetronimo);

				//check for and delete completed rows
				board->checkFullRows();
				//create new tetronimo that user controls
				generateTetronimo();
			}
			timer.stop();
			timer.start();
		}
		printf("%d\n", timer.getTime());
		if (tetronimo->movement == ROTATE) {
			tetronimo->rotateCCW();
			//Check for collisions caused by the rotations, try to solve by moving
			if (collisionDetector->checkCollision(tetronimo, board->boardBlocks)) {
				tetronimo->moveLeft();
				//if moving left caused another collision, try moving 1 right from original position 
				//check for collisions again
				if (collisionDetector->checkCollision(tetronimo, board->boardBlocks)) {
					tetronimo->moveRight();
					tetronimo->moveRight();
					//if moving left or right causes collisions, undo the rotatation and return to original position
					if (collisionDetector->checkCollision(tetronimo, board->boardBlocks)) {
						tetronimo->moveLeft();
						tetronimo->rotateCW();
					}
				}
			}
		}
		if (tetronimo->movement == DOWN) {
			tetronimo->moveDown();
			if (collisionDetector->belowCollisions(tetronimo, board->boardBlocks)) {
				tetronimo->moveUp();
				board->addBlocksToBoard(tetronimo);
				board->checkFullRows();
				generateTetronimo();
			}
		}

		if (tetronimo->movement == LEFT) {
			tetronimo->moveLeft();
			if (collisionDetector->checkCollision(tetronimo, board->boardBlocks)) {
				tetronimo->moveRight();
			}
		}
		if (tetronimo->movement == RIGHT) {
			tetronimo->moveRight();
			if (collisionDetector->checkCollision(tetronimo, board->boardBlocks)) {
				tetronimo->moveLeft();
			}
		}

		tetronimo->movement = NONE;
	}
	else {
		gameOver = false;
		app->popState();
	}
}


void playState::draw(App* app) {
	//draw background color
	SDL_SetRenderDrawColor(app->gRenderer, 0, 0, 0, 255);
	SDL_RenderClear(app->gRenderer);

	//draw board borders and grid
	board->drawBoardBorders(app->gRenderer);
	board->drawBoardGrid(app->gRenderer);

	//draw currenlty controlled tetronimo
	tetronimo->drawTetronimo(app->gRenderer);

	//draw next tetronimo
	nextTetro->drawTetronimo(app->gRenderer);

	SDL_SetRenderDrawColor(app->gRenderer, 255, 255, 255, 255);

	//draw next tetronimo border
	SDL_RenderDrawRect(app->gRenderer, &nextRect);

	//draw text UI
	scoreDisplay.draw(app->gRenderer);
	nextTetroInfo.draw(app->gRenderer);

	//Draw board blocks
	board->drawBoardBlocks(app->gRenderer);

	SDL_RenderPresent(app->gRenderer);
}

void playState::pause() {

}

void playState::resume() {

}

void playState::generateTetronimo() {
	//free tetronimo memory to prep for next tetronimo
	delete tetronimo;
	tetronimo = nextTetro;

	nextTetro = new Tetronimo((RIGHT_WALL + SCREEN_WIDTH)/2- 0.5*BLOCK_SIZE, CEILING + 3*BLOCK_SIZE);
	correctNextTetroPos();

	tetronimo->changeXY((LEFT_WALL + RIGHT_WALL) / 2, CEILING + BLOCK_SIZE);
	if (collisionDetector->belowCollisions(tetronimo, board->boardBlocks)) {
		gameOver = true;
	}

}

void playState::solveCollision(Tetronimo* tetro) {

}

void playState::correctNextTetroPos() {
	if (nextTetro->type == SQUARE) {
		nextTetro->changeXY(nextTetro->x - 0.5*BLOCK_SIZE, nextTetro->y);
	}
	else if (nextTetro->type == LINE) {
		nextTetro->changeXY(nextTetro->x - 0.5*BLOCK_SIZE, nextTetro->y - 0.5*BLOCK_SIZE);
	}
}