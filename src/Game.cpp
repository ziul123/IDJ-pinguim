#include "SDL2;SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#include <iostream>
#include <string>

#include "Game.h"
#include "State.h"

Game& Game::getInstance(){
	if (instance == nullptr)
		instance = new Game("200023314", 1024, 600);
	return *instance;
}

Game::Game(std::string title, int width, int height){
	if (instance != nullptr)
		throw;
	instance = this;
	int error = 0;
	error |= SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER);
	
	error |= IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF);

	error |= Mix_Init(MIX_INIT_MP3 | MIX_INIT_OGG);
	error |= Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024);
	error |= Mix_AllocateChannels(32);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	error |= window == nullptr;
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	error |= renderer == nullptr;
	if (error) {
		std::cout << SDL_GetError() << std::endl;
		throw;
	}
	
	state = new State();
}

Game::~Game(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	Mix_CloseAudio();
	Mix_Quit();

	IMG_Quit();

	SDL_Quit();
}

void Game::run(){
	while (!state->quitRequested()){
		state->update();
		state->render();
		SDL_RenderPresent(renderer);
		SDL_Delay(33);
	}
}
