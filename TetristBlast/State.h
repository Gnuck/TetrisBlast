//#pragma once
#ifndef STATE_H
#define STATE_H

#include "App.h"

class State {
public:
	virtual void init() = 0;
	virtual void cleanup() = 0;

	virtual void pause() = 0;
	virtual void resume() = 0;

	virtual void handleEvents(App* game) = 0;
	virtual void update(App* game) = 0;
	virtual void draw(App* game) = 0;

	void changeState(App* game, State* state) {
		game->changeState(state);
	}

protected:
	State() {}
};


#endif STATE_H