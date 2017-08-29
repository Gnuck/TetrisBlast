#pragma once
#include "SDL.h"

class Block
{
public:

	//Rect that defines the dimensions and coordinates of this block
	SDL_Rect rect;

	Block();
	~Block();

	Block::Block(int x, int y, int width, int height);

	Block::Block(SDL_Rect r);

	//move the block horizontally x units... negative x moves left, positive moves right
	void Block::moveHoriz(int x);
	//move the block vertically y units... negative y moves up, positive moves down
	void Block::moveVert(int y);
	
};

