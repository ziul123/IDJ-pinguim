#ifndef TEXT_H
#define TEXT_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"

#include <string>
#include <memory>

#include "Component.h"
#include "GameObject.h"

class Text: public Component {
	public:
		enum TextStyle {SOLID, SHADED, BLENDED};

		Text(GameObject& associated, std::string fontFile, int fontSize, TextStyle style, std::string text, SDL_Color color, int wp = 0);
		~Text();

		void Update(float dt);
		void Render();
		void Render(float x, float y);
		bool Is(std::string type);

		void SetText(std::string text);
		void SetColor(SDL_Color color);
		void SetStyle(TextStyle style);
		void SetFontFile(std::string fontFile);
		void SetFontSize(int fontSize);
		void SetWrapWidth(int wp);

	private:
		void RemakeTexture();

		std::shared_ptr<TTF_Font> font;
		SDL_Texture* texture;

		std::string text;
		TextStyle style;
		std::string fontFile;
		int fontSize;
		SDL_Color color;
		int wrapWidth;

};

#endif
