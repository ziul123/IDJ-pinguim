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
		Sprite(GameObject& associated, std::string file, int frameCount = 1, float frameTime = 1);
		~Sprite();

		void Render() override;
		void Update(float dt) override;
		bool Is(std::string type) override;

		void Render(float x, float y);

		void Open(std::string file);
		bool IsOpen(){return texture != nullptr;};

		void SetClip(int x, int y, int w, int h);
		int GetWidth(){return width * scale.x / frameCount;};
		int GetHeight(){return height * scale.y;};

		void SetScale(float scaleX, float scaleY);
		Vec2 GetScale() {return scale;};

		void SetFrame(int frame);
		void SetFrameCount(int fc);
		void SetFrameTime(float ft) {frameTime = ft;};

	private:
		SDL_Texture* texture;
		int width;
		int height;
		SDL_Rect clipRect;
		Vec2 scale;
		int frameCount;
		int currentFrame;
		float timeElapsed;
		float frameTime;
};

#endif
