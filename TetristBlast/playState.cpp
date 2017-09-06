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

	//Initialize text UI objects	
	scoreDisplay.init("Score = " + std::to_string(score),WHITE, (RIGHT_WALL + SCREEN_WIDTH) / 2, SCREEN_HEIGHT/2,14);
	resetInfo.init("R = Reset", WHITE, (RIGHT_WALL + SCREEN_WIDTH) / 2, scoreDisplay.rect.y + BLOCK_SIZE, 14);
	pauseInfo.init("P = Pause", WHITE, (RIGHT_WALL + SCREEN_WIDTH) / 2, resetInfo.rect.y + BLOCK_SIZE, 14);
	quitInfo.init("ESC = Quit to Menu", WHITE, (RIGHT_WALL + SCREEN_WIDTH) / 2, pauseInfo.rect.y + BLOCK_SIZE, 14);
	nextTetroInfo.init("Next Tetronimo", WHITE, (RIGHT_WALL + SCREEN_WIDTH) / 2,nextRect.y+nextRect.h+(int)(BLOCK_SIZE/2) , 14);
	nextTetroInfo.init("Next Tetronimo", WHITE, (RIGHT_WALL + SCREEN_WIDTH) / 2, nextRect.y + nextRect.h + (int)(BLOCK_SIZE / 2), 14);
	pauseNotify.init("PAUSED", WHITE, SCREEN_WIDTH / 2, 2*SCREEN_HEIGHT / 5, 75);
	gameOverText.init("GAME OVER", WHITE, SCREEN_WIDTH / 2, 2 * SCREEN_HEIGHT / 5, 75);

	gameOver = false;
}

void playState::handleEvents(App* app) {
	app->inputController->readInput();
	keysHeld = app->inputController->getInput();
	if (keysHeld[SDL_SCANCODE_UP]|| keysHeld[SDL_SCANCODE_W]) {
		tetronimo->movement = ROTATE;
		keysHeld[SDL_SCANCODE_UP] = false;
		keysHeld[SDL_SCANCODE_W] = false;
	}
	if (keysHeld[SDL_SCANCODE_DOWN] || keysHeld[SDL_SCANCODE_S]) {
		tetronimo->movement = DOWN;
		keysHeld[SDL_SCANCODE_DOWN] = false;
		keysHeld[SDL_SCANCODE_S] = false;
	}
	if (keysHeld[SDL_SCANCODE_LEFT] || keysHeld[SDL_SCANCODE_A]) {
		tetronimo->movement = LEFT;
		keysHeld[SDL_SCANCODE_LEFT] = false;
		keysHeld[SDL_SCANCODE_A] = false;
	}
	if (keysHeld[SDL_SCANCODE_RIGHT] || keysHeld[SDL_SCANCODE_D]) {
		tetronimo->movement = RIGHT;
		keysHeld[SDL_SCANCODE_RIGHT] = false;
		keysHeld[SDL_SCANCODE_D] = false;
	}
	if (keysHeld[SDL_SCANCODE_ESCAPE]) {
		app->popState();
		keysHeld[SDL_SCANCODE_ESCAPE] = false;
	}
	if (keysHeld[SDL_SCANCODE_P]) {
		pause();
		keysHeld[SDL_SCANCODE_P] = false;
	}
	if (keysHeld[SDL_SCANCODE_R]) {
		reset();
		keysHeld[SDL_SCANCODE_R] = false;
	}
}


void playState::update(App* app) {
	if (!gameOver && !paused) {
		int rowsDeleted = 0;
		if (timer.getTime() > 1000*speedUpFactor) {
			tetronimo->moveDown();
			if (collisionDetector->belowCollisions(tetronimo, board->boardBlocks)) {
				tetronimo->moveUp();
				board->addBlocksToBoard(tetronimo);

				//check for and delete completed rows, add deleted blocks to score
				rowsDeleted+= board->checkFullRows();
				if (rowsDeleted > 0) {
					updateScoreText(rowsDeleted);
				}
				//create new tetronimo that user controls
				generateTetronimo();
			}
			timer.stop();
			timer.start();
		}
		printf("%d\n", timer.getTime());
		if (tetronimo->movement == ROTATE) {
			tetronimo->rotateCCW();
			solveCollision(tetronimo);
		}
		if (tetronimo->movement == DOWN) {
			tetronimo->moveDown();
			if (collisionDetector->belowCollisions(tetronimo, board->boardBlocks)) {
				tetronimo->moveUp();
				board->addBlocksToBoard(tetronimo);

				//check for and delete completed rows, add deleted blocks to score
				rowsDeleted += board->checkFullRows();
				if (rowsDeleted > 0) {
					updateScoreText(rowsDeleted);
				}
				
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
	else if (!gameOver && paused) {
		//don't update game if game is paused
	}
	else {
		//gameOver = false;
		speedUpFactor = 1;
		score = 0;
		
		//app->popState();
	}
}


void playState::draw(App* app) {
	//draw background color(black)
	SDL_SetRenderDrawColor(app->gRenderer, 0, 0, 0, 255);
	SDL_RenderClear(app->gRenderer);

	board->drawBoardBorders(app->gRenderer);
	board->drawBoardGrid(app->gRenderer);

	tetronimo->drawTetronimo(app->gRenderer);

	nextTetro->drawTetronimo(app->gRenderer);

	//set render color to white
	SDL_SetRenderDrawColor(app->gRenderer, 255, 255, 255, 255);

	//draw next tetronimo border
	SDL_RenderDrawRect(app->gRenderer, &nextRect);

	//draw text UI
	scoreDisplay.draw(app->gRenderer);
	nextTetroInfo.draw(app->gRenderer);
	resetInfo.draw(app->gRenderer);
	pauseInfo.draw(app->gRenderer);
	quitInfo.draw(app->gRenderer);

	board->drawBoardBlocks(app->gRenderer);

	if (paused) {
		pauseNotify.draw(app->gRenderer);
	}
	if (gameOver) {
		gameOverText.draw(app->gRenderer);
	}

	SDL_RenderPresent(app->gRenderer);
}

void playState::pause() {
	if (paused) {
		timer.unpause();
		paused = false;
	}
	else {
		timer.pause();
		paused = true;
	}
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
	if (collisionDetector->checkCollision(tetronimo, board->boardBlocks)) {
		tetronimo->moveLeft();
		if (collisionDetector->checkCollision(tetronimo, board->boardBlocks)) {
			tetronimo->moveRight();
			tetronimo->moveRight();
			if (collisionDetector->checkCollision(tetronimo, board->boardBlocks)) {
				tetronimo->moveLeft();
				tetronimo->rotateCW();
			}
		}
	}
}

void playState::correctNextTetroPos() {
	if (nextTetro->type == SQUARE) {
		nextTetro->changeXY(nextTetro->x - 0.5*BLOCK_SIZE, nextTetro->y);
	}
	else if (nextTetro->type == LINE) {
		nextTetro->changeXY(nextTetro->x - 0.5*BLOCK_SIZE, nextTetro->y - 0.5*BLOCK_SIZE);
	}
}

void playState::reset() {
	delete tetronimo;
	tetronimo = new Tetronimo((LEFT_WALL + RIGHT_WALL) / 2, CEILING + BLOCK_SIZE);
	delete nextTetro;
	nextTetro = new Tetronimo((RIGHT_WALL + SCREEN_WIDTH) / 2 - 0.5*BLOCK_SIZE, CEILING + 3 * BLOCK_SIZE);
	correctNextTetroPos();

	delete board;
	board = new Board();
	gameOver = false;
	score = 0;
	updateScoreText(0);
}

void playState::cleanup() {
	delete tetronimo;

	delete nextTetro;

	delete board;
	delete collisionDetector;

	timer.stop();


	scoreDisplay.destroy();
	resetInfo.destroy();
	pauseInfo.destroy();
	quitInfo.destroy();
	nextTetroInfo.destroy();
	pauseNotify.destroy();
}

void playState::updateScoreText(int rowsDeleted) {
	score += 10*rowsDeleted;
	//speedup by 75% every 10 rows completed
	if (score % 100 == 0) {
		speedUpFactor *= 0.9;
	}

	scoreDisplay.updateText("Score = " + std::to_string(score));
}