#include "SDL2/SDL.h"

#include "State.h"

State::State(){
	quit = false;
	loadAssets();
}

void State::loadAssets(){

}

void State::update(float dt){
	if (SDL_QuitRequested())
		quit = true;
}

void State::render(){
	bg.render();
}

bool State::quitRequested(){
	return quit;
}
