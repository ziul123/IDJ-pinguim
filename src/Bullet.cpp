#include <string>
#include <cmath>

#include "Bullet.h"
#include "Camera.h"
#include "Component.h"
#include "GameObject.h"
#include "Game.h"
#include "Geometria.h"
#include "Sprite.h"
#include "Collider.h"
#include "utils.h"


Bullet::Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite, int fc, float ft, bool tp): Component(associated){
	Sprite* s = new Sprite(associated, sprite, fc, ft);
	associated.AddComponent(s);
	Collider* col = new Collider(associated);
	associated.AddComponent(col);
	distanceLeft = maxDistance;
	this->speed = Vec2(speed * std::cos(angle), speed * std::sin(angle));
	associated.angleDeg = angle*180/PI;
	targetsPlayer = tp;
}

void Bullet::Update(float dt){
	Rect nBox = associated.box + speed * dt;
	distanceLeft -= associated.box.GetCenter().Dist(nBox.GetCenter());
	associated.box = nBox;

	if (distanceLeft <= 0)
		associated.RequestDelete();
}

void Bullet::NotifyCollision(GameObject& other){
	if ((other.GetComponent("Alien") && !targetsPlayer) || (other.GetComponent("PenguinBody") && targetsPlayer))
		associated.RequestDelete();
}

bool Bullet::Is(std::string type){
	return type == "Bullet";
}
