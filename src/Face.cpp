#include <cstdlib>

#include "Face.h"
#include "GameObject.h"
#include "Sound.h"
#include "InputManager.h"
#include "Camera.h"

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

	InputManager& im = InputManager::GetInstance();

	float cX = Camera::pos.x;
	float cY = Camera::pos.y;

	if (im.MousePress(LEFT_MOUSE_BUTTON) && associated.box.Contains(Vec2((float)im.GetMouseX() + cX, (float)im.GetMouseY() + cY)))
		Damage(std::rand() % 10 + 10);
}
