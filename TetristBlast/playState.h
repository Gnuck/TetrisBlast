//#pragma once
#ifndef PLAYSTATE_H
#define PLAYSTATE_H
#include "App.h"
#include "State.h"
#include "Block.h"
#include "Board.h"
#include "Tetronimo.h"
#include "CollisionDetector.h"
#include "Timer.h"
#include "Text.h"

class playState : public State
{
public:



	void init();
	void cleanup();

	void handleEvents(App* app);
	void update(App* app);
	void draw(App* app);

	static playState* Instance() {
		return &m_playState;
	}


	
	int score = 0;

	Text scoreDisplay;

protected:
	playState();
	~playState();

private:
	static playState m_playState;

	//Game objects
	CollisionDetector* collisionDetector = NULL;
	Tetronimo* tetronimo = NULL;
	Tetronimo* nextTetro = NULL;
	//The board object where the game takes place, info about borders stationary blocks on the board
	Board* board = NULL;
	Timer timer;

	//Input data array
	bool* keysHeld = NULL;

	//Game state members
	void pause();
	void resume();
	void reset();
	bool paused;
	bool gameOver = false;
	float speedUpFactor = 1.0;
	
	//helper functions
	//assigns tetronimo and nextTetro a new game object, freeing old memory
	void generateTetronimo();
	//Solves the collision by evoking the correct response from the tetronimo
	void playState::solveCollision(Tetronimo* tetro);


	//NextTetro helpers
	//Defining rectangle for the square UI containing the next tetronimo
	SDL_Rect nextRect = { (RIGHT_WALL + SCREEN_WIDTH) / 2 - (int)(2.5*BLOCK_SIZE), CEILING + BLOCK_SIZE / 2, 5 * BLOCK_SIZE,5 * BLOCK_SIZE };
	void correctNextTetroPos();

	//Text members
	Text resetInfo=Text();
	Text quitInfo=Text();
	Text pauseInfo=Text();
	Text nextTetroInfo=Text();
	Text pauseNotify=Text();
	Text gameOverText=Text();

	//update score given rows deleted, score UI, and change speedup factor
	void updateScoreText(int rowsDeleted);
	

};


#endif
