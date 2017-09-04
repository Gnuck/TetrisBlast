#include "Text.h"



//Text::Text(std::string text, SDL_Color color,int x, int y, int font_size)
//{
//	font = TTF_OpenFont("ARCADECLASSIC.ttf", font_size);
//	this->text = text;
//	this->color = color;
//	rect = { x,y,0,0};
//
//	surfaceText = TTF_RenderText_Solid(font, this->text.c_str(), color);
//	this->rect.w = surfaceText->w;
//	this->rect.h = surfaceText->h;
//	rect.x = rect.x - rect.w / 2;
//
//}

//Text::Text() {
//	text ="";
//	color = { 0,0,0 };
//	rect = { 0,0,0,0 };
//}

Text::~Text(){}

void Text::init(std::string textIn, SDL_Color colorIn, int x, int y, int font_size) {
	font = TTF_OpenFont("ARCADECLASSIC.ttf", font_size);
	text = textIn;
	color = colorIn;
	rect = { x,y,0,0 };

	surfaceText = TTF_RenderText_Solid(font, text.c_str(), color);
	rect.w = surfaceText->w;
	rect.h = surfaceText->h;
	rect.x = rect.x - rect.w / 2;
}

void Text::draw(SDL_Renderer* renderer) {
	textureText = SDL_CreateTextureFromSurface(renderer, this->surfaceText);
	SDL_RenderCopy(renderer, textureText, NULL, &rect);
	
}

void Text::destroy() {
	SDL_DestroyTexture(textureText);
	SDL_FreeSurface(surfaceText);
}

void Text::changeColor(SDL_Color newColor) {
	color = newColor;
	surfaceText=TTF_RenderText_Solid(font, text.c_str(), color);
}
