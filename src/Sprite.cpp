#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <iostream>

#include "Sprite.h"
#include "Game.h"

Sprite::Sprite(){
	texture = nullptr;
}

Sprite::Sprite(std::string file){
	texture = nullptr;
	open(file);
}

Sprite::~Sprite(){
	if (isOpen())
		SDL_DestroyTexture(texture);
}

void Sprite::open(std::string file){
	if (texture != nullptr)
		SDL_DestroyTexture(texture);

	texture = IMG_LoadTexture(Game::getInstance().getRenderer(), file.c_str());
	if (texture == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		throw;
	}
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	setClip(x, y, width, height);
}

void Sprite::setClip(int x, int y, int w, int h){
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::Render(int x, int y){
	SDL_RenderCopy(Game::getInstance().getRenderer(), texture, clipRect, SDL_Rect(x, y, clipRect.w, clipRect.h));
}


