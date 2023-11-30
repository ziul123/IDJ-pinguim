#include <memory>
#include <string>
#include <cmath>
#include <cstdlib>

#include "Minion.h"
#include "Component.h"
#include "GameObject.h"
#include "Geometria.h"
#include "Sprite.h"
#include "Game.h"
#include "State.h"
#include "Bullet.h"
#include "Collider.h"
#include "utils.h"

#define ROT PI/8

Minion::Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg): Component(associated){
	Sprite* sprite = new Sprite(associated, "Recursos/img/minion.png");
	associated.AddComponent(sprite);
	Collider* col = new Collider(associated);
	associated.AddComponent(col);
	float scale = 1.0 + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(1.5-1.0)));
	sprite->SetScale(scale, scale); 
	this->alienCenter = alienCenter;
	arc = arcOffsetDeg;
}

Minion::~Minion(){
	/*
	auto* go = new GameObject();
	go->angleDeg = associated.angleDeg;
	auto* sprite = new Sprite(*go, "Recursos/img/miniondeath.png", 4, 0.2, 4*0.2);
	go->box.SetCenter(associated.box.GetCenter());
	go->AddComponent(sprite);
	Game::GetInstance().GetCurrentState().AddObject(go);
	*/
}

void Minion::Update(float dt){
	Vec2 inicial {120, 0};
	arc += ROT * dt;
	if (alienCenter.expired()){
		associated.RequestDelete();
		return;
	}
	Vec2 center = alienCenter.lock()->box.GetCenter();
	associated.box.SetCenter(inicial.GetRotated(arc) + center);

	associated.angleDeg = associated.box.GetCenter().Incline(center) * 180/PI - 90;
}

void Minion::Shoot(Vec2 pos){
	GameObject* go = new GameObject();
	go->box.SetCenter(associated.box.GetCenter());
	float angle = pos.Incline(associated.box.GetCenter());
	Bullet* bullet = new Bullet(*go, angle, 200.0, 20, 1000.0 , "Recursos/img/minionbullet2.png", 3, 0.3, true);
	go->AddComponent(bullet);
	Game::GetInstance().GetCurrentState().AddObject(go);
}

bool Minion::Is(std::string type){
	return type == "Minion";
}

