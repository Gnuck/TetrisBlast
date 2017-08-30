#include "Board.h"



Board::Board()
{
}


Board::~Board()
{
}

//Draws the borders for the play area
void Board::drawBoardBorders(SDL_Renderer* renderer) {

	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	//left wall
	SDL_RenderDrawLine(renderer, LEFT_WALL, CEILING, LEFT_WALL, FLOOR);
	//right wall
	SDL_RenderDrawLine(renderer, RIGHT_WALL, CEILING, RIGHT_WALL, FLOOR);
	//CEILING
	SDL_RenderDrawLine(renderer, LEFT_WALL, CEILING, RIGHT_WALL, CEILING);
	//FLOOR
	SDL_RenderDrawLine(renderer, LEFT_WALL, FLOOR, RIGHT_WALL, FLOOR);


}

void Board::drawBoardGrid(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	//vertical grid lines
	for (int i = 2; i < 11; i++) {
		for (int d = CEILING; d < FLOOR; d += 4) {
			SDL_RenderDrawPoint(renderer, i*LEFT_WALL, d);
		}
	}
	//horizontal grid lines
	for (int i = 2; i < 19; i++) {
		for (int d = LEFT_WALL; d < RIGHT_WALL; d += 4) {
			SDL_RenderDrawPoint(renderer, d, i*CEILING);
		}
	}
}