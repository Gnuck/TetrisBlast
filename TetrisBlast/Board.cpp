#include "Board.h"



Board::Board()
{
	//initialize the RowSizes Array
	for (int i = 0; i < BOARD_TILE_HEIGHT; i++) {
		RowSizes[i] = 0;
	}
}


Board::~Board()
{
}

//Draws the borders for the play area
void Board::drawBoardBorders(SDL_Renderer* renderer) {

	SDL_Rect border = { LEFT_WALL,CEILING,RIGHT_WALL - LEFT_WALL,FLOOR - CEILING };
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 255);
	SDL_RenderFillRect(renderer, &border);
	SDL_SetRenderDrawColor(renderer, 255 ,255, 255, 255);
	SDL_RenderDrawRect(renderer, &border);
	//SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	////left wall
	//SDL_RenderDrawLine(renderer, LEFT_WALL, CEILING, LEFT_WALL, FLOOR);
	////right wall
	//SDL_RenderDrawLine(renderer, RIGHT_WALL, CEILING, RIGHT_WALL, FLOOR);
	////CEILING
	//SDL_RenderDrawLine(renderer, LEFT_WALL, CEILING, RIGHT_WALL, CEILING);
	////FLOOR
	//SDL_RenderDrawLine(renderer, LEFT_WALL, FLOOR, RIGHT_WALL, FLOOR);


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

void Board::addBlocksToBoard(Tetronimo* tetro) {

	boardBlocks.push_back(tetro->origBlock);
	boardBlocks.push_back(tetro->secondBlock);
	boardBlocks.push_back(tetro->thirdBlock);
	boardBlocks.push_back(tetro->fourthBlock);
	
	//Update row data for each newly added block
	updateRowData(tetro->origBlock);
	updateRowData(tetro->secondBlock);
	updateRowData(tetro->thirdBlock);
	updateRowData(tetro->fourthBlock);

	
}


void Board::updateRowData(shared_ptr<Block> block) {
	
	RowSizes[block->getRow()] +=1;

}


void Board::drawBoardBlocks(SDL_Renderer* renderer) {
	vector<shared_ptr<Block>>::iterator it;
	for (it = boardBlocks.begin(); it != boardBlocks.end(); ++it) {
		(*it)->drawBlock(renderer);
	}
}

void Board::checkFullRows() {

	for (int i = BOARD_TILE_HEIGHT-1; i >=0; i--) {
		if (RowSizes[i] >= 10) {
			deleteCompletedRow(i);
			//incredment back up as above row moved down, must check current row again
			i++;
		}
	}
}

void Board::deleteCompletedRow(int rowDeleted) {

	vector<shared_ptr<Block>>::iterator it;
	for (it = boardBlocks.begin(); it != boardBlocks.end(); ) {
		int myrow = (*it)->getRow();
		if (myrow == rowDeleted) {
			it = boardBlocks.erase(it);
			RowSizes[myrow] -= 1;
		}
		else {
			if (myrow < rowDeleted) {
				((*it)->moveVert(BLOCK_SIZE));
				RowSizes[myrow] -= 1;
				//if not bottom row, update row data for block's new row
				if (myrow < BOARD_TILE_HEIGHT-1) {
					RowSizes[myrow + 1] += 1;
				}
			}
			++it;
		}
	}
}