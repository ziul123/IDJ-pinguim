#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_render.h"

#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

#include "Game.h"
#include "Resources.h"


std::shared_ptr<SDL_Texture> Resources::GetImage(std::string file){
	auto it = Resources::imageTable.find(file);
	if (it == Resources::imageTable.end()){
		auto texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());
		if (texture == nullptr)
			std::cout << "Falha ao abrir arquivo " << file << " em Resources::GetImage" << std::endl;
		auto sp = std::shared_ptr<SDL_Texture>(texture, sdl_deleter());
		it = Resources::imageTable.insert({file, sp}).first;
	}
	return it->second;
}

void Resources::ClearImages(){
	std::vector<std::string> keysToDelete;
    for (auto& [file, image] : imageTable) {
        if (image.unique()) {
            keysToDelete.push_back(file);
        }
    }
    for (auto& file : keysToDelete) {
        imageTable.erase(file);
    }
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
