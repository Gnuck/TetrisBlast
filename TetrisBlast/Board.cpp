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
	SDL_RenderDrawLine(renderer, leftWall, ceiling, leftWall, floor);
	//right wall
	SDL_RenderDrawLine(renderer, rightWall, ceiling, rightWall, floor);
	//ceiling
	SDL_RenderDrawLine(renderer, leftWall, ceiling, rightWall, ceiling);
	//floor
	SDL_RenderDrawLine(renderer, leftWall, floor, rightWall, floor);


}

void Board::drawBoardGrid(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	//vertical grid lines
	for (int i = 2; i < 11; i++) {
		for (int d = ceiling; d < floor; d += 4) {
			SDL_RenderDrawPoint(renderer, i*leftWall, d);
		}
	}
	//horizontal grid lines
	for (int i = 2; i < 19; i++) {
		for (int d = leftWall; d < rightWall; d += 4) {
			SDL_RenderDrawPoint(renderer, d, i*ceiling);
		}
	}
}