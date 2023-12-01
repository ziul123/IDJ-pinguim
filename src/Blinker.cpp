#include "Blinker.h"

Blinker::Blinker(GameObject& associated, float freq): Component(associated){
	this->freq = freq;
}

void Blinker::Update(float dt){
	timer.Update(dt);
	if (timer.Get() >= freq){
		associated.render = !associated.render;
		timer.Restart();
	}
}

bool Blinker::Is(std::string type){
	return type == "Blinker";
}
