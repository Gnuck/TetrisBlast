#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <cmath>
#include "App.h"
#include "Constants.h"

class Text
{
public:
	/*Params"
	* text: string value of the text to be drawn
	* color: color of the text to be drawn
	* x: x coordinate of the CENTERPOINT of this text object
	* y: y coodrinate of the CENTERPOINT of this text object*/
	//Text(std::string text, SDL_Color color,int x,int y,int font_size);



	Text();
	~Text();

	std::string text= "";
	SDL_Color color = WHITE;
	SDL_Rect rect = { 0,0,0,0 };

	TTF_Font* font= NULL;
	SDL_Surface* surfaceText = NULL;
	SDL_Texture* textureText = NULL;
	void draw(SDL_Renderer* renderer);

	void changeColor(SDL_Color newColor);


	void Text::updateText(std::string newText);

	void destroy();
	void init(std::string text, SDL_Color color, int x, int y, int font_size);
private:

	
};

