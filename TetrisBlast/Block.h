#pragma once
#include "SDL.h"
#include "Constants.h"
#include <stdlib.h>
#include <memory>
#include <vector>

using namespace std;

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

	//method for drawing this block
	void Block::drawBlock(SDL_Renderer* renderer);

	//change x value of block
	void Block::changeXY(int newX,int newY);

	void Block::changeY(int newY);


	//Get row for this block
	int Block::getRow();
};

