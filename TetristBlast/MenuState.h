#ifndef MENUSTATE_H
#define MENUSTATE_H

//#include "InputController.h"
#include "App.h"
#include "State.h"
#include "SDL_ttf.h"
#include "SDL.h"
#include "Text.h"


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

	bool playSelected = true;
	bool quitSelected = false;

	Text title=Text();
	Text blast=Text();

	Text playGame=Text();
	Text quitGame=Text();


protected:
	MenuState();
	~MenuState();

private:
	static MenuState m_MenuState;
};


#endif