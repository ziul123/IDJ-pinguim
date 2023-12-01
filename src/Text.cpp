#include "Text.h"

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "Resources.h"
#include "Colors.h"
#include "Game.h"
#include "Camera.h"
#include "utils.h"

Text::Text(GameObject& associated, std::string ff, int fs, TextStyle s, std::string t, SDL_Color c, int wp): Component(associated){
	fontFile = ff;
	fontSize = fs;
	style = s;
	text = t;
	color = c;
	wrapWidth = wp;
	texture = nullptr;
	RemakeTexture();
}

Text::~Text(){
	if (texture)
		SDL_DestroyTexture(texture);
}

void Text::Update(float dt){

}

void Text::Render(float x, float y){
	SDL_Renderer *renderer = Game::GetInstance().GetRenderer();
	SDL_Rect clipRect, dstrect;
	clipRect.x = 0;
	clipRect.y = 0;
	clipRect.w = associated.box.w;
	clipRect.h = associated.box.h;
	dstrect.x = x - Camera::pos.x;
	dstrect.y = y - Camera::pos.y;
	dstrect.w = clipRect.w;
	dstrect.h = clipRect.h;
	SDL_RenderCopyEx(renderer, texture, &clipRect, &dstrect, associated.angleDeg, nullptr, SDL_FLIP_NONE);
}

void Text::Render(){
	Render(associated.box.x, associated.box.y);
}

void Text::SetText(std::string t){
	text = t;
	RemakeTexture();
}

void Text::SetColor(SDL_Color c){
	color = c;
	RemakeTexture();
}

void Text::SetStyle(TextStyle s){
	style = s;
	RemakeTexture();
}

void Text::SetFontSize(int fs){
	fontSize = fs;
	RemakeTexture();
}

void Text::SetWrapWidth(int wp){
	wrapWidth = wp;
	RemakeTexture();
}

void Text::RemakeTexture(){
	if (texture){
		SDL_DestroyTexture(texture);
		texture = nullptr;
	}

	font = Resources::GetFont(fontFile, fontSize);

	SDL_Surface* surface;
	switch(style){
		case SOLID:
			surface = TTF_RenderUTF8_Solid(font.get(), text.c_str(), color);
			break;
		case SHADED:
			surface = TTF_RenderUTF8_Shaded(font.get(), text.c_str(), color, SDL_Color{0, 0, 0, 0});
			break;
		case BLENDED:
			surface = TTF_RenderUTF8_Blended_Wrapped(font.get(), text.c_str(), color, wrapWidth);
			break;
	}

	texture = SDL_CreateTextureFromSurface(Game::GetInstance().GetRenderer(), surface);
	SDL_FreeSurface(surface);
	if (color.a != 255) {
        SDL_SetTextureAlphaMod(texture, color.a);
    }

	int width, height;
	SDL_QueryTexture(texture, nullptr, nullptr, &width, &height);
	associated.box.w = width;
    associated.box.h = height;
}

bool Text::Is(std::string type){
	return type == "Text";
}
