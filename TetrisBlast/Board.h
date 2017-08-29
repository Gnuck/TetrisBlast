#pragma once
#include "Constants.h"
#include "SDL.h"
class Board
{
public:
	Board();
	~Board();

	//y value for the play area's floor
	int floor = 19*SCREEN_HEIGHT/20;
	//y value for the play area's ceiling
	int ceiling= SCREEN_HEIGHT /20;
	//x value for the play area's left wall
	int leftWall = SCREEN_WIDTH / 20;
	//x value for the play area's right wall
	int rightWall = 11*SCREEN_WIDTH / 20;

	//Used to draw borders for the play area
	void drawBoardBorders(SDL_Renderer* renderer);
	//Used to draw grid inside the play area
	void drawBoardGrid(SDL_Renderer* renderer);
};

