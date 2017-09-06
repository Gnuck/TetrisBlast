#pragma once
#include <SDL.h>
#include "Constants.h"
#include "SDL.h"
#include <stdlib.h>
#include <vector>
#include <memory>
#include "Block.h"
#include "Tetronimo.h"
#include <algorithm>

using namespace std;

class Board
{
public:
	Board();
	~Board();


	//Used to draw borders for the play area
	void drawBoardBorders(SDL_Renderer* renderer);
	//Used to draw grid inside the play area
	void drawBoardGrid(SDL_Renderer* renderer);

	//Vector used to contain all the block that are part of the board
	std::vector<std::shared_ptr<Block>> boardBlocks;

	//Given the four blocks from a tetronimo, adds them to the board
	void addBlocksToBoard(Tetronimo* tetro);

	//Draws the board blocks
	void drawBoardBlocks(SDL_Renderer* renderer);

	//Removes a complete row of blocks from the board, moves above rows down 1 row
	void deleteCompletedRow(int row);

	//keeps data about the current makeup of each row
	int RowSizes[BOARD_TILE_HEIGHT];

	//Given the newly added block, updates the row data to account for that block
	void updateRowData(shared_ptr<Block> block);

	//Checks all rows to see if they should be deleted, calls deleteCompletedRow to do so. returns number of rows deleted
	int checkFullRows();

};

