#include <algorithm>
#include <memory>
#include <vector>

#include "GameObject.h"
#include "Component.h"

GameObject::GameObject(bool r){
	isDead = false;
	started = false;
	render = r;
	angleDeg = 0;
}

GameObject::~GameObject(){
	components.clear();
}

void GameObject::Start(){
	for (int i = 0; i < (int) components.size(); i++)
		components[i]->Start();
	started = true;
}

void GameObject::Update(float dt){
	for (int i = 0; i < (int) components.size(); i++)
		components[i]->Update(dt);
}

void GameObject::Render(){
	if (!render)
		return;
	for (int i = 0; i < (int) components.size(); i++)
		components[i]->Render();
}

void GameObject::AddComponent(Component* cpt){
	components.emplace_back(cpt);
	if (started)
		cpt->Start();
}

void GameObject::RemoveComponent(Component* cpt){
	for (int i = 0; i < (int) components.size(); i++){
		if (components[i].get() == cpt){
			components.erase(components.begin()+i);
			return;
		}
	}
}

Component* GameObject::GetComponent(std::string type){
	Component* result = nullptr;
	for (int i = 0; i < (int) components.size(); i++){
		if (components[i]->Is(type)){
			result = components[i].get();
			break;
		}
	}
	return result;
}

void GameObject::NotifyCollision(GameObject& other){
	for (int i = 0; i < (int) components.size(); i++)
		components[i]->NotifyCollision(other);
}

void GameObject::SetRender(bool r){
	render = r;
}
