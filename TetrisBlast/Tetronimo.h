#pragma once
#include "Block.h"
#include "Constants.h"
#include <stdlib.h>
#include <vector>
#include <memory>

using namespace std;

class Tetronimo
{
public:
	Tetronimo();
	~Tetronimo();

	Movement movement = NONE;

	Tetronimo::Tetronimo(int x, int y);

	shared_ptr<Block> origBlock = NULL;

	//x-coordinates of other blocks, using origBlock as "origin"
	int xCord[3];
	int yCord[3];
	shared_ptr<Block> secondBlock = NULL;
	shared_ptr<Block> thirdBlock = NULL;
	shared_ptr<Block> fourthBlock = NULL;

	SDL_Color color;
	
	tetroPieces type;

	//x coordinate of the firstBlock
	int x;
	//y coordinate of the firstBlock
	int y;

	/*Draw all four blocks that make up this tetronimo*/
	void drawTetronimo(SDL_Renderer* renderer);

	//Move tetronimo up one unit
	void moveUp();
	//move tetronimo down one unit
	void moveDown();
	//move tetronimo left one unit
	void moveLeft();
	//move tetrnonimo right one unit
	void moveRight();

	//rotate the blocks CCW around the orig block
	void rotateCCW();

	void rotateCW();
	


	//
private:

	/**Given tetronimo type "type", initializes xCord and yCord arrays to
	their values that represent their position in relation to the origBlock*/
	void initBlockCords(tetroPieces type);
};

