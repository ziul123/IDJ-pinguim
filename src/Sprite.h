#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#include "SDL2/SDL.h"

class Sprite{
	public:
		Sprite();
		Sprite(std::string file);
		~Sprite();
		void open(std::string file);
		void setClip(int x, int y, int w, int h);
		void render(int x, int y);
		int getWidth(){return width;};
		int getHeight(){return height;};
		bool isOpen(){return texture != nullptr;};

	private:
		SDL_Texture* texture;
		int width;
		int height;
		SDL_Rect clipRect;
};

#endif
