#include "Tetronimo.h"



Tetronimo::Tetronimo()
{
}

Tetronimo::Tetronimo(int x, int y) {
	int r = rand() % 7;
	type = (tetroPieces) r;
	initBlockCords(type);

	origBlock = std::make_shared<Block>(x, y, BLOCK_SIZE, BLOCK_SIZE);
	secondBlock = std::make_shared<Block>(x + xCord[0] * BLOCK_SIZE, y + yCord[0] * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
	thirdBlock = std::make_shared<Block>(x + xCord[1] * BLOCK_SIZE, y + yCord[1] * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
	fourthBlock = std::make_shared<Block>(x + xCord[2] * BLOCK_SIZE, y + yCord[2] * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE);
}

Tetronimo::~Tetronimo()
{
}

void Tetronimo::initBlockCords(tetroPieces type) {

	switch (type) {
		case(LINE):
			//origin // |_||x||_||_|

			xCord[0]=-1;   //  |x||_||_||_|
			yCord[0] = 0;

			xCord[1] = 1;  //  |_||_||x||_|
			yCord[1] = 0;

			xCord[2] = 2;  //  |_||_||_||x|
			yCord[2] = 0;
			
			break;
		case(SEVEN):
			//origin //        |_|
			//           |_||x||_|

			xCord[0] = -1;	//	      |_|
			yCord[0] = 0;	//  |x||_||_|

			xCord[1] = 1;	//		  |_|
			yCord[1] = 0;	//  |_||_||x|

			xCord[2] = 1;	//	 	   |x|
			yCord[2] = -1;   //  |_||_||_|

			break;
		case(REV_SEVEN):
			//origin //  |_|
			//           |_||x||_|

			xCord[0] = -1;	//	|x|
			yCord[0] = -1;	//  |_||_||_|

			xCord[1] = -1;	//	|_|
			yCord[1] = 0;	//  |x||_||_|

			xCord[2] = 1;	//  |_|
			yCord[2] = 0;   //  |_||_||x|
			break;
		case(ZIGZAG):
			//origin //  |_||_|
			//              |x||_|

			xCord[0] = -1;	//	|x||_|
			yCord[0] = -1;	//     |_||_|

			xCord[1] = 0;	//	|_||x|
			yCord[1] = -1;	//     |_||_|

			xCord[2] = 1;	//  |_||_|
			yCord[2] = 0;   //     |_||x|
			break;
		case(REV_ZIGZAG):
			//origin //        |_||_|
			//              |_||x|

			xCord[0] = -1;	//	      |_||_|
			yCord[0] = 0;	//     |x||_|

			xCord[1] = 0;	//	      |x||_|
			yCord[1] = -1;	//     |_||_|

			xCord[2] = 1;	//         |_||x|
			yCord[2] = -1;   //     |_||_|

			break;
		case(CAPITAL_T):
			//origin //        |_|
			//              |_||x||_|

			xCord[0] = -1;	//	      |_|
			yCord[0] = 0;	//     |x||_||_|

			xCord[1] = 0;	//	      |x|
			yCord[1] = -1;	//     |_||_||_|

			xCord[2] = 1;	//        |_|
			yCord[2] = 0;   //     |_||_||x|
			break;
		case(SQUARE):
			//origin //     |_||_|
			//              |x||_|

			xCord[0] = 1;	//	   |_||_|
			yCord[0] = 0;	//     |_||x|

			xCord[1] = 0;	//	   |x||_|
			yCord[1] = -1;	//     |_||_|

			xCord[2] = 1;	//      |_||x|
			yCord[2] = -1;   //     |_||_|
			break;
		default:
			break;
	}
}

void Tetronimo::drawTetronimo(SDL_Renderer* renderer) {
	origBlock->drawBlock(renderer);
	secondBlock->drawBlock(renderer);
	thirdBlock->drawBlock(renderer);
	fourthBlock->drawBlock(renderer);
}

void Tetronimo::moveUp() {
	y -= BLOCK_SIZE;
	origBlock->moveVert(-BLOCK_SIZE);
	secondBlock->moveVert(-BLOCK_SIZE);
	thirdBlock->moveVert(-BLOCK_SIZE);
	fourthBlock->moveVert(-BLOCK_SIZE);
}

void Tetronimo::moveDown() {
	y += BLOCK_SIZE;
	origBlock->moveVert(BLOCK_SIZE);
	secondBlock->moveVert(BLOCK_SIZE);
	thirdBlock->moveVert(BLOCK_SIZE);
	fourthBlock->moveVert(BLOCK_SIZE);
}

void Tetronimo::moveLeft() {
	origBlock->moveHoriz(-BLOCK_SIZE);
	secondBlock->moveHoriz(-BLOCK_SIZE);
	thirdBlock->moveHoriz(-BLOCK_SIZE);
	fourthBlock->moveHoriz(-BLOCK_SIZE);
}

void Tetronimo::moveRight() {
	origBlock->moveHoriz(BLOCK_SIZE);
	secondBlock->moveHoriz(BLOCK_SIZE);
	thirdBlock->moveHoriz(BLOCK_SIZE);
	fourthBlock->moveHoriz(BLOCK_SIZE);
}

void Tetronimo::rotateCCW() {
	if (this->type == SQUARE) {

	}
	else {
		int orig_x = origBlock->rect.x;
		int orig_y = origBlock->rect.y;
		int temp;
		//rotate the coordinate system
		for (int i = 0; i < 3; i++) {
			temp = yCord[i];
			yCord[i] = -xCord[i];
			xCord[i] = temp;
		}
		//apply the changes
		secondBlock->changeXY(BLOCK_SIZE*xCord[0] + orig_x, orig_y + BLOCK_SIZE*yCord[0]);
		thirdBlock->changeXY(orig_x + BLOCK_SIZE*xCord[1], orig_y + BLOCK_SIZE*yCord[1]);
		fourthBlock->changeXY(orig_x + BLOCK_SIZE*xCord[2], orig_y + BLOCK_SIZE*yCord[2]);
	}
}

void Tetronimo::rotateCW() {
	if (this->type == SQUARE) {

	}
	else {
		int orig_x = origBlock->rect.x;
		int orig_y = origBlock->rect.y;
		int temp;
		//rotate the coordinate system
		for (int i = 0; i < 3; i++) {
			temp = yCord[i];
			yCord[i] = xCord[i];
			xCord[i] = -temp;
		}
		//apply the changes
		secondBlock->changeXY(BLOCK_SIZE*xCord[0] + orig_x, orig_y + BLOCK_SIZE*yCord[0]);
		thirdBlock->changeXY(orig_x + BLOCK_SIZE*xCord[1], orig_y + BLOCK_SIZE*yCord[1]);
		fourthBlock->changeXY(orig_x + BLOCK_SIZE*xCord[2], orig_y + BLOCK_SIZE*yCord[2]);
	}
}



