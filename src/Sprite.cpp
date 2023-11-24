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

Sprite::Sprite(GameObject& associated, std::string file, int fc, float ft): Sprite(associated){
	frameCount = fc;
	frameTime = ft;
	scale = {1, 1};
	currentFrame = 0;
	timeElapsed = 0;
	Open(file);
}

Sprite::~Sprite(){
}

void Sprite::Open(std::string file){
	texture = Resources::GetImage(file);
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	SetClip(0, 0, width/frameCount, height);
	associated.box.w = width/frameCount;
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
	dstrect.w = clipRect.w * scale.x;
	dstrect.h = clipRect.h * scale.y;
	SDL_RenderCopyEx(renderer, texture, &clipRect, &dstrect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
}

void Sprite::Render(){
	Render(associated.box.x, associated.box.y);
}

void Sprite::Update(float dt){
	if ((timeElapsed += dt) > frameTime){
		int frameWidth = width/frameCount;
		if (++currentFrame >= frameCount)
			currentFrame = 0;
		SetClip(currentFrame * frameWidth, 0, frameWidth, height);
		timeElapsed = 0;
	}
}

void Sprite::SetScale(float scaleX, float scaleY){
	if (scaleX)
		scale.x = scaleX;

	if (scaleY)
		scale.y = scaleY;

	Vec2 oldCenter = associated.box.GetCenter();
	associated.box.w *= scaleX;
	associated.box.h *= scaleY;
	associated.box.SetCenter(oldCenter);
}

void Sprite::SetFrame(int frame){
	currentFrame = frame;
	int frameWidth = width/frameCount;
	SetClip(currentFrame * frameWidth, 0, frameWidth, height);
	timeElapsed = 0;
}

void Sprite::SetFrameCount(int fc){
	frameCount = fc;
	currentFrame = 0;
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	associated.box.w = width * scale.x;
	associated.box.h = height * scale.y;
}

bool Sprite::Is(std::string type){
	return type == "Sprite";
}
