#include "Block.h"


Block::~Block()
{
}

Block::Block(int x, int y, int width, int height,SDL_Color color)
{
	rect = {x,y,width,height};
	this->color = color;
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
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, 200);
	SDL_RenderFillRect(renderer, &rect);

	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	//top line
	SDL_RenderDrawLine(renderer,rect.x, rect.y, rect.x + rect.w , rect.y);
	//left line
	SDL_RenderDrawLine(renderer, rect.x, rect.y, rect.x, rect.y + rect.h );
	//right line
	SDL_RenderDrawLine(renderer, rect.x + rect.w , rect.y, rect.x + rect.w , rect.y + rect.h );
	//bottom line
	SDL_RenderDrawLine(renderer, rect.x, rect.y + rect.h, rect.x + rect.w , rect.y + rect.h );

}

void Block::changeXY(int newX, int newY) {
	this->rect.x = newX;
	this->rect.y = newY;
}

void Block::changeY(int newY) {
	this->rect.y = newY;
}

int Block::getRow() {
	for (int i = 0; i < BOARD_TILE_HEIGHT; i++) {
		if (CEILING + i*BLOCK_SIZE == this->rect.y) {
			return i;
		}
	}
	return -1; //block not on board
}
