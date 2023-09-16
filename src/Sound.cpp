#include "SDL2/SDL_mixer.h"

#include <iostream>

#include "Sound.h"


Sound::Sound(GameObject& associated): Component(associated){
	chunk = nullptr;
}

Sound::Sound(GameObject& associated, std::string file): Sound(associated){
	Open(file);
}

void Sound::Play(int times){
	channel = Mix_PlayChannel(-1, chunk, times-1);
}

void Sound::Stop(){
	if (chunk != nullptr)
		Mix_HaltChannel(channel);
}

void Sound::Open(std::string file){
	chunk = Mix_LoadWAV(file.c_str());
	if (chunk == nullptr)
		std::cout << "Falha ao abrir arquivo " << file << " em Sound::Open" << std::endl;
}

Sound::~Sound(){
	if (chunk != nullptr) {
		Mix_HaltChannel(channel);
		Mix_FreeChunk(chunk);
	}
}

bool Sound::Is(std::string type){
	return type == "Sound";
}

bool Sound::IsPlaying(){
	return Mix_Playing(channel);
}
