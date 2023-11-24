#include <algorithm>
#include <cmath>
#include <queue>
#include <string>
#include <memory>
#include <vector>
#include <cstdlib>

#include "Alien.h"
#include "Camera.h"
#include "InputManager.h"
#include "Geometria.h"
#include "Sprite.h"
#include "Minion.h"
#include "Game.h"
#include "State.h"
#include "Collider.h"
#include "Bullet.h"
#include "Collider.h"
#include "utils.h"


Alien::Alien(GameObject& associated, int nMinions): Component(associated){
	Sprite* sprite = new Sprite(associated, "Recursos/img/alien.png");
	associated.AddComponent(sprite);
	Collider* col = new Collider(associated);
	associated.AddComponent(col);
	hp = 30;
	speed = Vec2(0.0, 0.0);
	this->nMinions = nMinions;
}

void Alien::Start(){
	State& state = Game::GetInstance().GetState();
	auto alien = state.GetObjectPtr(&associated);

	for (int i=0; i < nMinions; i++){
		GameObject* go = new GameObject();
		Minion* m = new Minion(*go, alien, 2*PI*i/nMinions);
		go->AddComponent(m);
		minionArray.push_back(state.AddObject(go));
	}

}

Alien::~Alien(){
	for (int i = 0; i < (int) minionArray.size(); i++)
		minionArray[i].lock()->RequestDelete();
	minionArray.clear();
}

void Alien::Update(float dt){
	InputManager& im = InputManager::GetInstance();

	float cX = Camera::pos.x;
	float cY = Camera::pos.y;

	if (im.MousePress(LEFT_MOUSE_BUTTON))
		taskQueue.push(Action(Action::SHOOT, (float)im.GetMouseX() + cX, (float)im.GetMouseY() + cY));

	if (im.MousePress(RIGHT_MOUSE_BUTTON))
		taskQueue.push(Action(Action::MOVE, (float)im.GetMouseX() + cX, (float)im.GetMouseY() + cY));

	if (!taskQueue.empty()){
		Action a = taskQueue.front();
		switch (a.type) {
			case Action::SHOOT:
			{
				auto m = std::min_element(minionArray.begin(), minionArray.end(), [a](auto x, auto y) mutable {return x.lock()->box.GetCenter().Dist(a.pos) < y.lock()->box.GetCenter().Dist(a.pos);});
				((Minion*)(*m).lock()->GetComponent("Minion"))->Shoot(a.pos);
				taskQueue.pop();
				break;
			}

			case Action::MOVE:
				Vec2 pos = associated.box.GetCenter();
				if (pos == a.pos){
					taskQueue.pop();
					break;
				}
				speed = (a.pos - pos).Normalizar() * dt * 200;
				Vec2 nPos = pos + speed;
				if (nPos.Dist(a.pos) < 10.0){
					nPos.x = a.pos.x;
					nPos.y = a.pos.y;
					taskQueue.pop();
				}
				associated.box.SetCenter(nPos);
				break;
		}
	}
/*
	if (hp <= 0)
		associated.RequestDelete();
*/
	associated.angleDeg += 0.5;
}

void Alien::NotifyCollision(GameObject& other){
	auto bullet = (Bullet*) other.GetComponent("Bullet");
	if (bullet && !bullet->targetsPlayer){
		log("Alien collision");
		log(bullet->targetsPlayer);
		log(associated.box.x);
		log(" ");
		log(associated.box.y);
		log(" ");
		log(associated.box.w);
		log(" ");
		log(associated.box.h);
		log(" ");
		hp -= bullet->GetDamage();
	}
}

bool Alien::Is(std::string type){
	return type == "Alien";
}
