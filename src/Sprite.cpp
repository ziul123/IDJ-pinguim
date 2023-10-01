#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include <iostream>

#include "Sprite.h"
#include "Game.h"
#include "GameObject.h"
#include "Resources.h"
#include "Camera.h"

Sprite::Sprite(GameObject& associated): Component(associated){
	texture = nullptr;
}

Sprite::Sprite(GameObject& associated, std::string file): Sprite(associated){
	Open(file);
}

Sprite::~Sprite(){
}

void Sprite::Open(std::string file){
	texture = Resources::GetImage(file);
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

void Sprite::Render(float x, float y){
	SDL_Renderer *renderer = Game::GetInstance().GetRenderer();
	SDL_Rect dstrect;
	dstrect.x = x - Camera::pos.x;
	dstrect.y = y - Camera::pos.y;
	dstrect.w = clipRect.w;
	dstrect.h = clipRect.h;
	SDL_RenderCopy(renderer, texture, &clipRect, &dstrect);
}

void Sprite::Render(){
	Render(associated.box.x, associated.box.y);
}

bool Sprite::Is(std::string type){
	return type == "Sprite";
}
