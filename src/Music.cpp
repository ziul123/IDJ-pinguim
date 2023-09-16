#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

#include <iostream>
#include <string>

#include "Music.h"

Music::Music(){
	music = nullptr;
}

Music::Music(std::string file){
	Open(file);
}

void Music::Play(int times){
	Mix_PlayMusic(music, times);
	Mix_VolumeMusic(32);
}

void Music::Stop(int msToStop){
	Mix_FadeOutMusic(msToStop);
}

void Music::Open(std::string file){
	if ((music = Mix_LoadMUS(file.c_str())) == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		//throw;
	}
}

bool Music::IsOpen(){
	return music == nullptr;
}

Music::~Music(){
	Stop();
	Mix_FreeMusic(music);
}
