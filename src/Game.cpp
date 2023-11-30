#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"

#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

#include "Game.h"
#include "State.h"
#include "Resources.h"
#include "InputManager.h"
#include "utils.h"

Game* Game::instance = nullptr;

Game& Game::GetInstance(){
	if (instance == nullptr)
		instance = new Game("200023314", SCREEN_WIDTH, SCREEN_HEIGHT);
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
	
	storedState = nullptr;
	dt = 0.0;
	frameStart = 0;
	srand (static_cast <unsigned> (time(0)));
}

Game::~Game(){
	if (storedState)
		delete storedState;

	while (!stateStack.empty())
		stateStack.pop();

	Resources::ClearImages();
	Resources::ClearMusics();
	Resources::ClearSounds();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	Mix_CloseAudio();
	Mix_Quit();

	IMG_Quit();

	SDL_Quit();
}

State& Game::GetCurrentState(){
	return *stateStack.top();
}

void Game::Push(State* state){
	storedState = state;
}

void Game::Run(){
	if (!storedState) {
		log("Error: No initial state!");
		throw;
	}

	stateStack.emplace(storedState);
	storedState = nullptr;

	while (!stateStack.empty() && !GetCurrentState().QuitRequested()){
		if (stateStack.top()->PopRequested()){
			stateStack.pop();
			stateStack.top()->Resume();
		}

		if (storedState){
			stateStack.top()->Pause();
			stateStack.emplace(storedState);
			stateStack.top()->Start();
			storedState = nullptr;
		}

		CalculateDeltaTime();
		InputManager::GetInstance().Update();
		stateStack.top()->Update(dt);
		stateStack.top()->Render();
		SDL_RenderPresent(renderer);
		SDL_Delay(33);
	}
}

void Game::CalculateDeltaTime(){
	int32_t ticks = SDL_GetTicks();
    dt = (float)(ticks - frameStart) / 1000.0f;
    frameStart = ticks;
}
