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
#include "utils.h"


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

std::shared_ptr<Mix_Music> Resources::GetMusic(std::string file){
	auto it = musicTable.find(file);
	if (it == musicTable.end()){
		auto music = Mix_LoadMUS(file.c_str());
		if (music == nullptr)
			std::cout << "Falha ao abrir arquivo " << file << " em Resources::GetMusic" << std::endl;
		auto sp = std::shared_ptr<Mix_Music>(music, sdl_deleter());
		it = musicTable.insert({file, sp}).first;
	}
	return it->second;
}

void Resources::ClearMusics(){
	std::vector<std::string> keysToDelete;
    for (auto& [file, music] : musicTable) {
        if (music.unique()) {
            keysToDelete.push_back(file);
        }
    }
    for (auto& file : keysToDelete) {
        musicTable.erase(file);
    }
}

std::shared_ptr<Mix_Chunk> Resources::GetSound(std::string file){
	auto it = soundTable.find(file);
	if (it == soundTable.end()){
		auto chunk = Mix_LoadWAV(file.c_str());
		if (chunk == nullptr)
			std::cout << "Falha ao abrir arquivo " << file << " em Resources::GetSound" << std::endl;
		auto sp = std::shared_ptr<Mix_Chunk>(chunk, sdl_deleter());
		it = soundTable.insert({file, sp}).first;
	}
	return it->second;
}

void Resources::ClearSounds(){
	std::vector<std::string> keysToDelete;
    for (auto& [file, chunk] : soundTable) {
        if (chunk.unique()) {
            keysToDelete.push_back(file);
        }
    }
    for (auto& file : keysToDelete) {
        soundTable.erase(file);
    }
}

std::shared_ptr<TTF_Font> Resources::GetFont(std::string file, int fontSize){
	auto key = file + std::to_string(fontSize);
	auto it = fontTable.find(key);
	if (it == fontTable.end()){
		auto font = TTF_OpenFont(file.c_str(), fontSize);
		if (font == nullptr)
			std::cout << "Falha ao abrir arquivo " << file << " em Resources::GetFont" << std::endl;
		auto sp = std::shared_ptr<TTF_Font>(font, sdl_deleter());
		it = fontTable.insert({key, sp}).first;
	}
	return it->second;
}

void Resources::ClearFonts(){
	std::vector<std::string> keysToDelete;
    for (auto& [file, font] : fontTable) {
        if (font.unique()) {
            keysToDelete.push_back(file);
        }
    }
    for (auto& file : keysToDelete) {
        fontTable.erase(file);
    }
}

void Resources::ClearAll(){
	ClearImages();
	ClearSounds();
	ClearMusics();
	ClearFonts();
}
