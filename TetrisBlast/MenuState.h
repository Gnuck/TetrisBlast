#ifndef MENUSTATE_H
#define MENUSTATE_H

//#include "InputController.h"
#include "App.h"
#include "State.h"


class MenuState : public State
{
public:

	void init();
	void cleanup();

	void pause();
	void resume();

	void handleEvents(App* app);
	void update(App* app);
	void draw(App* app);

	static MenuState* Instance() {
		return &m_MenuState;
	}

protected:
	MenuState();
	~MenuState();

private:
	static MenuState m_MenuState;

	//SDL_Surface*  bg;
};

#endif