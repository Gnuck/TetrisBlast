#include "Block.h"


Block::~Block()
{
}

Block::Block(int x, int y, int width, int height)
{

	rect = {x,y,width,height};
}

Block::Block(SDL_Rect r)
{	
	rect = r;
}

//add argument to Blocks current x position. Positive x moves right, negative moves left
void Block::moveHoriz(int x) {
	rect.x += x;
}

void Block::moveVert(int y) {
	rect.y += y;
}

void Block::drawBlock(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, &rect);
}

void Block::changeXY(int newX, int newY) {
	this->rect.x = newX;
	this->rect.y = newY;
}

