#pragma once
#include "SDL.h"
#include "Constants.h"
#include <stdlib.h>
#include <memory>

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

	/*checks for a collision to the right of this block given
	* the x coordinate of the collider (the left wall of the collider to check)*/
	bool Block::collRight(int collider);

	/*checks for collisiont to left of this block given
	* the x coordinate of the colldier (the right wall of the collider)*/
	bool Block::collLeft(int collider);

	/*checks for a collision below this block block given the y coordinate of the collider
	* the y coordinate of the collider(the top wall of the collider*/
	bool Block::collBelow(int collider);

	//check for collision to left and right against a given block
	bool Block::collBlock(Block collider);
};

