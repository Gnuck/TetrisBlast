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

void Block::drawBlock(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0xFF, 0xFF);
	SDL_RenderFillRect(renderer, &rect);

	SDL_SetRenderDrawColor(renderer, 0x00, 0xFF, 0x00, 0xFF);
	//top line
	SDL_RenderDrawLine(renderer,rect.x, rect.y, rect.x + rect.w , rect.y);
	//left line
	SDL_RenderDrawLine(renderer, rect.x, rect.y, rect.x, rect.y + rect.h );
	//right line
	SDL_RenderDrawLine(renderer, rect.x + rect.w , rect.y, rect.x + rect.w , rect.y + rect.h );
	//bottom line
	SDL_RenderDrawLine(renderer, rect.x, rect.y + rect.h, rect.x + rect.w , rect.y + rect.h );

}

void Block::changeXY(int newX, int newY) {
	this->rect.x = newX;
	this->rect.y = newY;
}

bool Block::collRight(int collider) {
	return (this->rect.x >= collider);
}

bool Block::collLeft(int collider) {
	return (this->rect.x < collider);
}

bool Block::collBelow(int collider) {
	return(this->rect.y  >= collider);
}

bool Block::collBlock(shared_ptr<Block> collider) {
	return (collider->rect.y == this->rect.y) && (collider->rect.x == this->rect.x);
}

bool Block::checkCollBlocks(vector<shared_ptr<Block>> blocks) {
	vector<shared_ptr<Block>>::iterator it;
	for (it = blocks.begin(); it != blocks.end(); ++it) {
		if (collBlock(*it)) {
			return true;
		}
	}
	return false;
}