#ifndef SPRITE_H
#define SPRITE_H

#include "SDL2/SDL.h"

#include <string>

#include "Component.h"
#include "GameObject.h"
#include "Geometria.h"

class Sprite: public Component {
	public:
		Sprite(GameObject& associated);
		Sprite(GameObject& associated, std::string file);
		~Sprite();
		void Open(std::string file);
		void SetClip(int x, int y, int w, int h);
		void Render(float x, float y);
		void Render() override;
		int GetWidth(){return width * scale.x;};
		int GetHeight(){return height * scale.y;};
		bool IsOpen(){return texture != nullptr;};
		void Update(float dt) override {};
		bool Is(std::string type) override;
		void SetScaleX(float scaleX, float scaleY);
		Vec2 GetScale() {return scale;};

	private:
		SDL_Texture* texture;
		int width;
		int height;
		SDL_Rect clipRect;
		Vec2 scale;
};

#endif
