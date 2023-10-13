#include <string>
#include <cmath>

#include "Bullet.h"
#include "Component.h"
#include "GameObject.h"
#include "Geometria.h"
#include "Sprite.h"


Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite): Component(associated){
	Sprite* s = new Sprite(associated, sprite);
	associated.AddComponent(s);
	distanceLeft = maxDistance;
	this->speed = Vec2(speed * std::cos(angle), speed * std::sin(angle));
}

void Bullet::Update(float dt){
	Rect nBox = associated.box + speed * dt;
	distanceLeft -= associated.box.GetCenter().Dist(nBox.GetCenter());
	associated.box = nBox;

	if (distanceLeft <= 0)
		associated.RequestDelete();
}

bool Bullet::Is(std::string type){
	return type == "Bullet";
}
