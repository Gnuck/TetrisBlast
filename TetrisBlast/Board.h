#pragma once
#include "Constants.h"
#include "SDL.h"
class Board
{
public:
	Board();
	~Board();



	//Used to draw borders for the play area
	void drawBoardBorders(SDL_Renderer* renderer);
	//Used to draw grid inside the play area
	void drawBoardGrid(SDL_Renderer* renderer);
};

