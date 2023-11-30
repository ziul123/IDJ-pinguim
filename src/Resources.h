#ifndef RESOURCES_H
#define RESOURCES_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

#include <string>
#include <unordered_map>
#include <memory>

class Resources {
	public:
		static std::shared_ptr<SDL_Texture> GetImage(std::string file);
		static void ClearImages();

		static Mix_Music* GetMusic(std::string file);
		static void ClearMusics();

		static Mix_Chunk* GetSound(std::string file);
		static void ClearSounds();

	private:
		
		inline static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
		inline static std::unordered_map<std::string, Mix_Music*> musicTable;
		inline static std::unordered_map<std::string, Mix_Chunk*> soundTable;

		struct sdl_deleter{
		  void operator()(SDL_Texture *p) const { SDL_DestroyTexture(p); }
		  void operator()(Mix_Music *p) const { Mix_FreeMusic(p); }
		  void operator()(Mix_Chunk *p) const { Mix_FreeChunk(p); }
		};

};

#endif
