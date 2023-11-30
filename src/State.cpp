#include "State.h"

#include <memory>
#include <vector>

#include "GameObject.h"

State::State(){
	popRequested = false;
	quitRequested = false;
	started = false;
}

State::~State(){
	objectArray.clear();
}

std::weak_ptr<GameObject> State::AddObject(GameObject* go){
	std::shared_ptr<GameObject> p{ go };
	objectArray.push_back(p);
	if (started)
		p->Start();

	std::weak_ptr<GameObject> w(p);
	return w;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go){
	std::weak_ptr<GameObject> w;
	for (int i = 0; i < (int) objectArray.size(); i++){
		if (objectArray[i].get() == go)
			w = objectArray[i];
	}
	return w;
}

void State::StartArray(){
	for (int i = 0; i < (int) objectArray.size(); i++)
		objectArray[i]->Start();
}

void State::UpdateArray(float dt){
	for (int i = 0; i < (int) objectArray.size(); i++)
		objectArray[i]->Update(dt);
}

void State::RenderArray(){
	for (int i = 0; i < (int) objectArray.size(); i++)
		objectArray[i]->Render();
}
