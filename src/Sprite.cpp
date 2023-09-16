#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <iostream>

#include "Sprite.h"
#include "Game.h"
#include "GameObject.h"

Sprite::Sprite(GameObject& associated): Component(associated){
	texture = nullptr;
}

Sprite::Sprite(GameObject& associated, std::string file): Sprite(associated){
	Open(file);
}

Sprite::~Sprite(){
	if (IsOpen())
		SDL_DestroyTexture(texture);
}

void Sprite::Open(std::string file){
	if (texture != nullptr)
		SDL_DestroyTexture(texture);

	texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
	if (texture == nullptr)
		std::cout << "Falha ao abrir arquivo " << file << " em Sprite::Open" << std::endl;

	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	SetClip(0, 0, width, height);
	associated.box.w = width;
	associated.box.h = height;
}

void Sprite::SetClip(int x, int y, int w, int h){
	clipRect.x = x;
	clipRect.y = y;
	clipRect.w = w;
	clipRect.h = h;
}

void Sprite::Render(){
	int x = associated.box.x;
	int y = associated.box.y;
	SDL_Renderer *renderer = Game::GetInstance().GetRenderer();
	SDL_Rect dstrect;
	dstrect.x = x;
	dstrect.y = y;
	dstrect.w = clipRect.w;
	dstrect.h = clipRect.h;
	SDL_RenderCopy(renderer, texture, &clipRect, &dstrect);
}

bool Sprite::Is(std::string type){
	return type == "Sprite";
}
