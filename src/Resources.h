#ifndef RESOURCES_H
#define RESOURCES_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"

#include <string>
#include <unordered_map>
#include <memory>

class Resources {
	public:
		static std::shared_ptr<SDL_Texture> GetImage(std::string file);
		static void ClearImages();

		static std::shared_ptr<Mix_Music> GetMusic(std::string file);
		static void ClearMusics();

		static std::shared_ptr<Mix_Chunk> GetSound(std::string file);
		static void ClearSounds();

		static std::shared_ptr<TTF_Font> GetFont(std::string file, int fontSize);
		static void ClearFonts();

		static void ClearAll();

	private:
		
		inline static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
		inline static std::unordered_map<std::string, std::shared_ptr<Mix_Music>> musicTable;
		inline static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> soundTable;
		inline static std::unordered_map<std::string, std::shared_ptr<TTF_Font>> fontTable;

		struct sdl_deleter{
		  void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
		  void operator()(Mix_Music *p) const { Mix_FreeMusic(p); }
		  void operator()(Mix_Chunk *p) const { Mix_FreeChunk(p); }
		  void operator()(TTF_Font *p) const {TTF_CloseFont(p); }
		};

};

#endif
