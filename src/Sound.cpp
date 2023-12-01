#include "SDL2/SDL_mixer.h"

#include <iostream>

#include "Resources.h"
#include "Sound.h"


Sound::Sound(GameObject& associated): Component(associated){
	chunk = nullptr;
}

Sound::Sound(GameObject& associated, std::string file): Sound(associated){
	Open(file);
}

void Sound::Play(int times){
	channel = Mix_PlayChannel(-1, chunk.get(), times-1);
	Mix_VolumeChunk(chunk.get(), 32);
}

void Sound::Stop(){
	if (chunk)
		Mix_HaltChannel(channel);
}

void Sound::Open(std::string file){
	chunk = Resources::GetSound(file);
}

Sound::~Sound(){
	if (chunk) {
		Mix_HaltChannel(channel);
	}
}

bool Sound::Is(std::string type){
	return type == "Sound";
}

bool Sound::IsPlaying(){
	return Mix_Playing(channel);
}
