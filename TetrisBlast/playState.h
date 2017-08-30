//#pragma once
#ifndef PLAYSTATE_H
#define PLAYSTATE_H
#include "App.h"
#include "State.h"
#include "Block.h"
#include "Board.h"
#include "Tetronimo.h"

class playState : public State
{
public:


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
protected:
	playState();
	~playState();

private:
	static playState m_playState;
};


#endif
