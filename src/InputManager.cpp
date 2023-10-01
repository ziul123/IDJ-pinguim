#include "SDL2/SDL.h"

#include <unordered_map>

#include "InputManager.h"

InputManager& InputManager::GetInstance(){
	static InputManager instance;
	return instance;
}

InputManager::InputManager(): mouseState{}, mouseUpdate{}, quitRequested(false), updateCounter(0), mouseX(0), mouseY(0){}

void InputManager::Update(){
	SDL_Event event;

	while (SDL_PollEvent(&event)){
		SDL_GetMouseState(&mouseX, &mouseY);
		quitRequested = false;
		updateCounter++;

		switch (event.type){
			case SDL_QUIT:
				quitRequested = true;
				break;

			case SDL_MOUSEBUTTONDOWN:
				mouseState[event.button.button] = true;
				mouseUpdate[event.button.button] = updateCounter;
				break;
			
			case SDL_MOUSEBUTTONUP:
				mouseState[event.button.button] = false;
				mouseUpdate[event.button.button] = updateCounter;
				break;

			case SDL_KEYDOWN:
				if (!event.key.repeat){
					keyState[event.key.keysym.sym] = true;
					keyUpdate[event.key.keysym.sym] = updateCounter;
				}
				break;

			case SDL_KEYUP:
				keyState[event.key.keysym.sym] = false;
				keyUpdate[event.key.keysym.sym] = updateCounter;
				break;
		}
	}
}

bool InputManager::KeyPress(int key){
	return updateCounter == keyUpdate[key] ? keyState[key] : false;
}

bool InputManager::KeyRelease(int key){
	return updateCounter == keyUpdate[key] ? !keyState[key] : false;
}

bool InputManager::IsKeyDown(int key){
	return keyState[key];
}

bool InputManager::MousePress(int button){
	return updateCounter == mouseUpdate[button] ? mouseState[button] : false;
}

bool InputManager::MouseRelease(int button){
	return updateCounter == mouseUpdate[button] ? !mouseState[button] : false;
}

bool InputManager::IsMouseDown(int button){
	return mouseState[button];
}

