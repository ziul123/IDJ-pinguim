#include "SDL2/SDL.h"

#include "State.h"

State::State(){
	quit = false;
	loadAssets();
}

void State::loadAssets(){
	bg.open("Recursos/img/ocean.jpg");
	music.open("Recursos/audio/stageState.ogg");
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
