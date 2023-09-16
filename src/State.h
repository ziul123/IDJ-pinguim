#ifndef STATE_H
#define STATE_H

#include <memory>
#include <vector>

#include "Music.h"
#include "Sprite.h"
#include "GameObject.h"

class State{
	public:
		State();
		~State();
		bool QuitRequested();
		void LoadAssets();
		void Update(float dt);
		void Render();

	private:
		void Input();
		void AddObject(int mouseX, int mouseY);
		Music music;
		bool quitRequested;
		std::vector<std::unique_ptr<GameObject>> objectArray;
		
};

#endif
