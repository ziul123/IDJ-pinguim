#ifndef SPRITE_H
#define SPRITE_H

#include "SDL2/SDL.h"

#include <string>

#include "Component.h"
#include "GameObject.h"

class Sprite: public Component {
	public:
		Sprite(GameObject& associated);
		Sprite(GameObject& associated, std::string file);
		~Sprite();
		void Open(std::string file);
		void SetClip(int x, int y, int w, int h);
		void Render(float x, float y);
		void Render() override;
		int GetWidth(){return width;};
		int GetHeight(){return height;};
		bool IsOpen(){return texture != nullptr;};
		void Update(float dt) override {};
		bool Is(std::string type) override;

	private:
		SDL_Texture* texture;
		int width;
		int height;
		SDL_Rect clipRect;
};

#endif
