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

	bool* keysHeld = NULL;

	void pause();
	void resume();

	CollisionDetector* collisionDetector = NULL;

	//Current tetronimo the play controls
	Tetronimo* tetronimo = NULL;

	//Next tetronimo to be spawned;
	Tetronimo* nextTetro = NULL;
	//The board object where the game takes place, keeps information about the play borders and the stationary blocks/tetronimos
	//currently on the board
	Board* board = NULL;

	//assigns tetronimo a new Tetronimo object, freeing the last tetronimo object
	void generateTetronimo();

	//Solves the collision by evoking the correct response from the tetronimo
	void playState::solveCollision(Tetronimo* tetro);
	Timer timer;
	bool gameOver = false;
	Text resetInfo;
	Text quitInfo;
	Text pauseInfo;
	Text nextTetroInfo;
	static playState m_playState;
	void correctNextTetroPos();

	//Defining rectangle for the square UI containing the next tetronimo
	SDL_Rect nextRect = { (RIGHT_WALL + SCREEN_WIDTH) / 2 - (int)(2.5*BLOCK_SIZE), CEILING + BLOCK_SIZE / 2, 5 * BLOCK_SIZE,5 * BLOCK_SIZE };

};


#endif
