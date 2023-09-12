#include "SDL2/SDL.h"

#include "State.h"

State::State(){
	quitRequested = false;
	LoadAssets();
}

void State::LoadAssets(){
	bg.Open("Recursos/img/ocean.jpg");
	music.Open("Recursos/audio/stageState.ogg");
	music.Play();
}

void State::Update(float dt){
	if (SDL_QuitRequested())
		quitRequested = true;
}

void State::Render(){
	bg.Render(0, 0);
}

bool State::QuitRequested(){
	return quitRequested;
}
