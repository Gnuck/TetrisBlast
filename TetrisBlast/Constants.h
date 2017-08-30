#pragma once
//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;

//Block width/height
const int BLOCK_SIZE = 32;

//y value for the play area's floor
const int FLOOR = 19 * SCREEN_HEIGHT / 20;
//y value for the play area's ceiling
const int CEILING = SCREEN_HEIGHT / 20;
//x value for the play area's left wall
const int LEFT_WALL = SCREEN_WIDTH / 20;
//x value for the play area's right wall
const int RIGHT_WALL = 11 * SCREEN_WIDTH / 20;

enum tetroPieces {
	LINE,
	SEVEN,
	REV_SEVEN,
	ZIGZAG,
	REV_ZIGZAG,
	CAPITAL_T,
	SQUARE
};
