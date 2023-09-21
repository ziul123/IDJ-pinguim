#ifndef RESOURCES_H
#define RESOURCES_H

#include "SDL2/SDL.h"

#include <string>
#include <unordered_map>

class Resources {
	public:
		static SDL_Texture* GetImage(std::string file);
		static void ClearImages();

		static Mix_Music* GetMusic(std::string file);
		static void ClearMusics();

		static Mix_Chunk* GetSound(std::string file);
		static void ClearSounds();

	private:
		
		inline static std::unordered_map<std::string, SDL_Texture*> imageTable;
		inline static std::unordered_map<std::string, Mix_Music*> musicTable;
		inline static std::unordered_map<std::string, Mix_Chunk*> soundTable;

};

#endif
