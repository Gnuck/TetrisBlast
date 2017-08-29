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