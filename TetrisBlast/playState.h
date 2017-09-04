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

class playState : public State
{
public:

	CollisionDetector* collisionDetector = NULL;

	void init();
	void cleanup();

	void pause();
	void resume();

	void handleEvents(App* app);
	void update(App* app);
	void draw(App* app);

	static playState* Instance() {
		return &m_playState;
	}
	//Current tetronimo the play controls
	Tetronimo* tetronimo = NULL;

	//The board object where the game takes place, keeps information about the play borders and the stationary blocks/tetronimos
	//currently on the board
	Board* board = NULL;

	//assigns tetronimo a new Tetronimo object
	void generateTetronimo();

	//frees the current tetronimo object and adds its block to the board
	void destroyTetronimo();

	//Solves the collision by evoking the correct response from the tetronimo
	void playState::solveCollision(Tetronimo* tetro);

	Timer timer;
	
	bool gameOver = false;
protected:
	playState();
	~playState();

private:
	static playState m_playState;
};


#endif
