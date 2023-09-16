#include <algorithm>
#include <memory>
#include <vector>

#include "GameObject.h"
#include "Component.h"

GameObject::GameObject(){
	isDead = false;
}

GameObject::~GameObject(){
	components.clear();
}

void GameObject::Update(float dt){
	for (int i = 0; i < (int) components.size(); i++)
		components[i]->Update(dt);
}

void GameObject::Render(){
	for (int i = 0; i < (int) components.size(); i++)
		components[i]->Render();
}

void GameObject::AddComponent(Component* cpt){
	components.emplace_back(cpt);
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
