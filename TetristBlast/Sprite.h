#include "SDL.h"
#include <iostream>

class Sprite {

private:
	SDL_Surface *image;
	SDL_Rect rect;

	int origin_x, origin_y;

public:

	Sprite();
	~Sprite();

	Sprite(Uint32 color, int x, int y, int w = 48, int h = 64) {};

	void update() {
		//Can be overridden!
	}

	void draw(SDL_Surface *destination) {
		SDL_BlitSurface(image, NULL, destination, &rect);
	}
};