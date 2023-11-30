#ifndef GAME_H
#define GAME_H

#include "SDL2/SDL.h"

#include <string>
#include <stack>
#include <memory>

#include "State.h"

class Game {
	public:
		~Game();

		SDL_Renderer* GetRenderer(){return renderer;};
		State& GetCurrentState();
		static Game& GetInstance();

		void Push(State* state);

		void Run();

		float GetDeltaTime(){return dt;};
	
	private:
		Game(std::string title, int width, int height);
		void CalculateDeltaTime();
		static Game* instance;
		SDL_Window* window;
		SDL_Renderer* renderer;
		State* storedState;
		std::stack<std::unique_ptr<State>> stateStack;	
		int frameStart;
		float dt;

};
#endif
