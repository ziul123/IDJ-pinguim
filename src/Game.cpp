#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#include <iostream>
#include <string>

#include "Game.h"
#include "State.h"
#include "Resources.h"
#include "InputManager.h"

Game* Game::instance = nullptr;

Game& Game::GetInstance(){
	if (instance == nullptr)
		instance = new Game("200023314", 1024, 600);
	return *instance;
}

Game::Game(std::string title, int width, int height){
	if (instance != nullptr){
		std::cout << "Erro: Game instanciado mais de uma vez" << std::endl;
		throw;
	}
	instance = this;
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
		std::cout << "SDL_Init error: " << SDL_GetError() << std::endl;
	
	if (IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF) != (IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF))
		std::cout << "IMG_Init error: " << SDL_GetError() << std::endl;

	if (Mix_Init(MIX_INIT_OGG) != MIX_INIT_OGG)
		std::cout << "Mix_Init error: " << SDL_GetError() << std::endl;

	if(Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) != 0)
		std::cout << "Mix_OpenAudio error: " << SDL_GetError() << std::endl;

	Mix_AllocateChannels(32);

	window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (window == nullptr || renderer == nullptr)
		std::cout << "Create window/renderer error: " << SDL_GetError() << std::endl;
	
	state = new State();
	dt = 0.0;
	frameStart = 0;
}

Game::~Game(){
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	Mix_CloseAudio();
	Mix_Quit();

	IMG_Quit();

	SDL_Quit();
}

void Game::Run(){
	while (!state->QuitRequested()){
		CalculateDeltaTime();
		InputManager::GetInstance().Update();
		state->Update(dt);
		state->Render();
		SDL_RenderPresent(renderer);
		SDL_Delay(33);
	}
	Resources::ClearImages();
	Resources::ClearMusics();
	Resources::ClearSounds();
}

void Game::CalculateDeltaTime(){
	int32_t ticks = SDL_GetTicks();
    dt = (float)(ticks - frameStart) / 1000.0f;
    frameStart = ticks;
}
