#include "MenuState.h"
#include "playState.h"


MenuState MenuState::m_MenuState;

MenuState::MenuState()
{
}


MenuState::~MenuState()
{
}

void MenuState::init() {
	title.init("TETRIS", WHITE, SCREEN_WIDTH / 2, BLOCK_SIZE, 80);
	blast.init("BLAST!", WHITE, SCREEN_WIDTH / 2 + title.rect.w / 3, title.rect.y + title.rect.h, 20);

	playGame.init("PLAY GAME", WHITE, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 25);
	quitGame.init("QUIT", WHITE, SCREEN_WIDTH / 2, playGame.rect.y + playGame.rect.h+BLOCK_SIZE, 25);
}

void MenuState::cleanup() {

}

void MenuState::pause() {

}

void MenuState::resume() {

}

void MenuState::handleEvents(App* app) {
	app->inputController->readInput();

	bool* keysHeld = app->inputController->getInput();
	if (keysHeld[SDL_SCANCODE_DOWN]) {
		if (playSelected) {
			playSelected = false;
			quitSelected = true;
		}
	}
	if (keysHeld[SDL_SCANCODE_UP]) {
		if (quitSelected) {
			playSelected = true;
			quitSelected = false;
		}
	}
	if (keysHeld[SDL_SCANCODE_DOWN]) {

	}
	if (keysHeld[SDL_SCANCODE_LEFT]) {

	}
	if (keysHeld[SDL_SCANCODE_RIGHT]) {

	}
	if (keysHeld[SDL_SCANCODE_RETURN]) {
		if (playSelected) {
			app->pushState(playState::Instance());
			keysHeld[SDL_SCANCODE_RETURN] = false;
		}
		else {
			app->inputController->pressedQuit = true;
		}
	}
}

void MenuState::update(App* app)
{

	if (playSelected) {
		playGame.changeColor(WHITE);
		quitGame.changeColor(SILVER);
	}
	else {
		playGame.changeColor(SILVER);
		quitGame.changeColor(WHITE);
	}
}

void MenuState::draw(App* app) {
	SDL_SetRenderDrawColor(app->gRenderer, 0, 0, 0, 0);
	SDL_RenderClear(app->gRenderer);

	//Text title = Text("TETRIS", WHITE, SCREEN_WIDTH / 2, 0, 150);
	//Text blast = Text("BLAST!", WHITE, SCREEN_WIDTH / 2 + title.rect.w / 3, title.rect.y + 3 * title.rect.h / 4, 50);

	//Text playGame = Text("PLAY GAME", WHITE, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 25);
	//Text quitGame = Text("QUIT", WHITE, SCREEN_WIDTH / 2, playGame.rect.y + playGame.rect.h, 25);

	//if (playSelected) {
	//	playGame.changeColor(WHITE);
	//	quitGame.changeColor(SILVER);
	//}
	//else {
	//	playGame.changeColor(SILVER);
	//	quitGame.changeColor(WHITE);
	//}



	title.draw(app->gRenderer);
	blast.draw(app->gRenderer);
	playGame.draw(app->gRenderer);
	quitGame.draw(app->gRenderer);

	SDL_RenderPresent(app->gRenderer);
}