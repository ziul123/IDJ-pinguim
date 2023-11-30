#ifndef STATE_H
#define STATE_H

#include <memory>
#include <vector>

#include "GameObject.h"

class State {
	public:
		State();
		virtual ~State();

		virtual void LoadAssets() {};
		virtual void Update(float dt) = 0;
		virtual void Render() = 0;

		virtual void Start() {};
		virtual void Pause() {};
		virtual void Resume() {};

		virtual std::weak_ptr<GameObject> AddObject(GameObject* obj);
		virtual std::weak_ptr<GameObject> GetObjectPtr(GameObject* obj);

		bool PopRequested() {return popRequested;};
		bool QuitRequested() {return quitRequested;};

	protected:
		virtual void StartArray();
		virtual void UpdateArray(float dt);
		virtual void RenderArray();

		bool popRequested;
		bool quitRequested;
		bool started;

		std::vector<std::shared_ptr<GameObject>> objectArray;

};

#endif
