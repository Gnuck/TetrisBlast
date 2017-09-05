#include "CollisionDetector.h"



CollisionDetector::CollisionDetector()
{
}


CollisionDetector::~CollisionDetector()
{
}

bool CollisionDetector::checkCollision(Tetronimo* tetro, vector<shared_ptr<Block>> blocks) {
	return collRight(tetro->origBlock,RIGHT_WALL) || collLeft(tetro->origBlock,LEFT_WALL)
		|| collRight(tetro->secondBlock,RIGHT_WALL) || collLeft(tetro->secondBlock,LEFT_WALL)
		|| collRight(tetro->thirdBlock,RIGHT_WALL) || collLeft(tetro->thirdBlock,LEFT_WALL)
		|| collRight(tetro->fourthBlock,RIGHT_WALL) || collLeft(tetro->fourthBlock,LEFT_WALL)
		|| collBelow(tetro->origBlock, FLOOR) || collBelow(tetro->secondBlock, FLOOR)
		|| collBelow(tetro->thirdBlock, FLOOR)|| collBelow(tetro->fourthBlock, FLOOR)
		|| checkCollBlocks(tetro->origBlock,blocks) || checkCollBlocks(tetro->secondBlock,blocks)
		|| checkCollBlocks(tetro->thirdBlock,blocks) || checkCollBlocks(tetro->fourthBlock,blocks);

}

bool CollisionDetector::leftWallCollision(Tetronimo* tetro) {
	return collLeft(tetro->origBlock,LEFT_WALL) || collLeft(tetro->secondBlock,LEFT_WALL)
		|| collLeft(tetro->thirdBlock,LEFT_WALL) || collLeft(tetro->fourthBlock,LEFT_WALL);
}

bool CollisionDetector::rightWallCollision(Tetronimo* tetro) {
	return collRight(tetro->origBlock,RIGHT_WALL) || collRight(tetro->secondBlock,RIGHT_WALL)
		|| collRight(tetro->thirdBlock,RIGHT_WALL) || collRight(tetro->fourthBlock,RIGHT_WALL);
}

bool CollisionDetector::belowCollisions(Tetronimo* tetro, vector<shared_ptr<Block>> blocks) {
	return collBelow(tetro->origBlock,FLOOR) || collBelow(tetro->secondBlock, FLOOR)
		|| collBelow(tetro->thirdBlock,FLOOR) || collBelow(tetro->fourthBlock,FLOOR)
		|| checkCollBlocks(tetro->origBlock,blocks) || checkCollBlocks(tetro->secondBlock,blocks)
		|| checkCollBlocks(tetro->thirdBlock,blocks) || checkCollBlocks(tetro->fourthBlock,blocks);
}


bool CollisionDetector::collRight(shared_ptr<Block> block, int collider) {
	return (block->rect.x >= collider);
}

bool CollisionDetector::collLeft(shared_ptr<Block> block,int collider) {
	return (block->rect.x < collider);
}

bool CollisionDetector::collBelow(shared_ptr<Block> block, int collider) {
	return(block->rect.y >= collider);
}

bool CollisionDetector::collBlock(shared_ptr<Block> block, shared_ptr<Block> collider) {
	return (collider->rect.y == block->rect.y) && (collider->rect.x == block->rect.x);
}

bool CollisionDetector::checkCollBlocks(shared_ptr<Block> block, vector<shared_ptr<Block>> blocks) {
	vector<shared_ptr<Block>>::iterator it;
	for (it = blocks.begin(); it != blocks.end(); ++it) {
		if (collBlock(block,*it)) {
			return true;
		}
	}
	return false;
}
