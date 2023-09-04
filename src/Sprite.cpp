#include "Sprite.h"

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
}
