#ifndef STATE_H
#define STATE_H

#include <memory>
#include <vector>

#include "Music.h"
#include "Sprite.h"
#include "GameObject.h"

class State {
	public:
		State();
		~State();
		bool QuitRequested(){return quitRequested;};
		void LoadAssets();
		void Update(float dt);
		void Render();
		void Start();
		std::weak_ptr<GameObject> AddObject(GameObject* go);
		std::weak_ptr<GameObject> GetObjectPtr(GameObject* go);

	private:
		void Input();
		void AddObject(int mouseX, int mouseY);
		Music music;
		bool quitRequested;
		std::vector<std::shared_ptr<GameObject>> objectArray;
		bool started;
		
};

#endif
