#include "Face.h"
#include "GameObject.h"
#include "Sound.h"

Face::Face(GameObject& associated, int hp): Component(associated){
	hitpoints = hp;
}

void Face::Damage(int damage){
	if ((hitpoints -= damage) <= 0){
		((Sound*) associated.GetComponent("Sound"))->Play();
	}
}

bool Face::Is(std::string type){
	return type == "Face";
}

void Face::Update(float dt){
	if (hitpoints <= 0){
		if (!((Sound*) associated.GetComponent("Sound"))->IsPlaying())
			associated.RequestDelete();
	}
}
