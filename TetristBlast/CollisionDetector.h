#pragma once
#include "Block.h"
#include "Constants.h"
#include <stdlib.h>
#include <vector>
#include <memory>
#include "Tetronimo.h"

class CollisionDetector
{
public:
	CollisionDetector();
	~CollisionDetector();

	//check all blocks in this tetronimo for a left or right collision with a border
	bool checkCollision(Tetronimo* tetro, vector<shared_ptr<Block>> blocks);

	//check all blocks for collision with left wall
	bool leftWallCollision(Tetronimo* tetro);

	//check all blocks for collision with right wall
	bool rightWallCollision(Tetronimo* tetro);

	//Checks all blocks for a collision below (currently with the floor)
	bool belowCollisions(Tetronimo* tetro, vector<shared_ptr<Block>> blocks);

	/*checks for a collision to the right of this block given
	* the x coordinate of the collider (the left wall of the collider to check)*/
	bool collRight(shared_ptr<Block> block, int collider);

	/*checks for collisiont to left of this block given
	* the x coordinate of the colldier (the right wall of the collider)*/
	bool collLeft(shared_ptr<Block> block, int collider);

	/*checks for a collision below this block block given the y coordinate of the collider
	* the y coordinate of the collider(the top wall of the collider*/
	bool collBelow(shared_ptr<Block> block, int collider);

	//check for collision to left and right against a given block
	bool collBlock(shared_ptr<Block> block, shared_ptr<Block> collider);

	//Check for collision between this block and every block in the given list of blocks
	bool checkCollBlocks(shared_ptr<Block> block, vector<shared_ptr<Block>> blocks);
};

