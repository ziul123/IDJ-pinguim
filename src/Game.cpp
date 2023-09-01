#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#include <iostream>
#include <string>

#include "Game.h"
#include "State.h"

Game& Game::getInstance(){
	if (instance == nullptr)
		instance = new Game();
	return *instance;
}

Game::Game(std::string title, int width, int height){
	if (instance != nullptr)
		throw;
	instance = this;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) != 0)
		std::cout << SDL_GetError();
	
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);
	int Mix_Init(int flags)
	int Mix_OpenAudio(int frequency, Uint16 format, int channels, int chunksize)
	int Mix_AllocateChannels(int numchans)

}	
