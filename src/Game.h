#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"

#include <string>

#include "State.h"

class Game {
	public:
		~Game(){};
		void run();
		SDL_Renderer* getRenderer(){return *renderer;};
		State& getState(){return *state;};
		static Game& getInstance();
	
	private:
		Game(std::string title, int width, int height);
		Game* instance;
		SDL_Window* window;
		SDL_Renderer* renderer;
		State* state;	
};
#endif
