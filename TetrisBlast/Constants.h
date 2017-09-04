#pragma once
#include "SDL.h"
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
//Number of vertical grid spaces
const int BOARD_TILE_HEIGHT = 18;
//Number of horizontal grid spaces
const int BOARD_TILE_WIDTH = 10;

enum tetroPieces {
	LINE,
	SEVEN,
	REV_SEVEN,
	ZIGZAG,
	REV_ZIGZAG,
	CAPITAL_T,
	SQUARE
};

enum Movement {
	LEFT,
	RIGHT,
	DOWN,
	NONE,
	ROTATE

};



const SDL_Color WHITE = { 255,255,255 };
const SDL_Color ORANGE = { 255,128,0 };
const SDL_Color BLUE = { 0,0,204 };
const SDL_Color YELLOW = { 255,255,0 };
const SDL_Color CYAN = { 0,255,255 };
const SDL_Color RED = { 255,0,0 };
const SDL_Color PURPLE = { 153,0,76 };
const SDL_Color SILVER = { 192,192,192 };
const SDL_Color GREEN = { 0,204,0 };
const SDL_Color LIME = { 128,255,0 };
const SDL_Color BLACK = { 0,0,0 };
const SDL_Color MAGENTA = { 139 ,0 ,139 };

const SDL_Color RETRO_RED = { 221,87,55 };
const SDL_Color RETRO_ORANGE = { 227,169,96 };
const SDL_Color RETRO_GREEN = { 82,148,107 };
const SDL_Color RETRO_BLUE = { 79,133,154 };
const SDL_Color RETRO_TEAL = { 108,182,177};
const SDL_Color RETRO_PINK = { 255,192,203 };

const SDL_Color colorArray[6] = {RETRO_RED,RETRO_ORANGE,RETRO_GREEN,RETRO_BLUE,RETRO_TEAL,RETRO_PINK};

