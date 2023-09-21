#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#include <iostream>
#include <string>
#include <unordered_map>

#include "Game.h"
#include "Resources.h"


SDL_Texture* Resources::GetImage(std::string file){
	SDL_Texture* texture;
	if (Resources::imageTable.find(file) == Resources::imageTable.end()){
		texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
		if (texture == nullptr)
			std::cout << "Falha ao abrir arquivo " << file << " em Resources::GetImage" << std::endl;
		Resources::imageTable[file] = texture;
	} else {
		texture = Resources::imageTable[file];
	}
	return texture;
}

void Resources::ClearImages(){
	for (const auto& kv: Resources::imageTable)
		SDL_DestroyTexture(kv.second);
	Resources::imageTable.clear();
}

Mix_Music* Resources::GetMusic(std::string file){
	Mix_Music* music;
	if (Resources::musicTable.find(file) == Resources::musicTable.end()){
		music = Mix_LoadMUS(file.c_str());
		if (music == nullptr)
			std::cout << "Falha ao abrir arquivo " << file << " em Resources::GetMusic" << std::endl;
		Resources::musicTable[file] = music;
	} else {
		music = Resources::musicTable[file];
	}
	return music;
}

void Resources::ClearMusics(){
	for (const auto& kv: Resources::musicTable)
		Mix_FreeMusic(kv.second);
	Resources::musicTable.clear();
}

Mix_Chunk* Resources::GetSound(std::string file){
	Mix_Chunk* chunk;
	if (Resources::soundTable.find(file) == Resources::soundTable.end()){
		chunk = Mix_LoadWAV(file.c_str());
		if (chunk == nullptr)
			std::cout << "Falha ao abrir arquivo " << file << " em Resources::GetSound" << std::endl;
	} else {
		chunk = Resources::soundTable[file];
	}
	return chunk;
}

void Resources::ClearSounds(){
	for (const auto& kv: Resources::soundTable)
		Mix_FreeChunk(kv.second);
	Resources::soundTable.clear();
}
