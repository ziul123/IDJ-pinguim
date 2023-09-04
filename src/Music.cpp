#include "SDL2/SDL.h"
#include "SDL2/SDL_mixer.h"

#include <iostream>
#include <string>

#include "Music.h"

Music::Music(){
	music = nullptr;
}

Music::Music(std::string file){
	open(file);
}

void Music::play(int times = -1){
	Mix_PlayMusic(music, times);
}

void Music::stop(int msToStop = 1500){
	Mix_FadeOutMusic(msToStop);
}

void Music::open(std::string file){
	if ((music = Mix_LoadMUS(file.c_str())) == nullptr) {
		std::cout << SDL_GetError() << std::endl;
		throw;
	}
}

void Music::isOpen(){
	return music == nullptr;
}

Music::~Music(){
	stop();
	Mix_FreeMusic(music);
}
