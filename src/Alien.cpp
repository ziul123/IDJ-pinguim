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
#include "Sound.h"
#include "PenguinBody.h"
#include "utils.h"

int Alien::alienCount = 0;


Alien::Alien(GameObject& associated, int nMinions): Component(associated){
	Sprite* sprite = new Sprite(associated, "Recursos/img/alien.png");
	associated.AddComponent(sprite);
	Collider* col = new Collider(associated);
	associated.AddComponent(col);
	hp = 30;
	speed = Vec2(0.0, 0.0);
	this->nMinions = nMinions;
	alienCount++;
}

void Alien::Start(){
	State& s = Game::GetInstance().GetCurrentState();
	auto alien = s.GetObjectPtr(&associated);

	for (int i=0; i < nMinions; i++){
		GameObject* go = new GameObject();
		Minion* m = new Minion(*go, alien, 2*PI*i/nMinions);
		go->AddComponent(m);
		minionArray.push_back(s.AddObject(go));
	}
	state = RESTING;
	restTimer.Restart();
}

Alien::~Alien(){
	for (int i = 0; i < (int) minionArray.size(); i++)
		minionArray[i].lock()->RequestDelete();
	minionArray.clear();
	alienCount--;
}

void Alien::Update(float dt){

	if (PenguinBody::player){
		switch (state){
			case RESTING:
				restTimer.Update(dt);
				if (restTimer.Get() >= 3){
					Vec2 p = PenguinBody::player->GetPos();
					destination = p;
					state = MOVING;
				}
				break;
			case MOVING:
				Vec2 pos = associated.box.GetCenter();
				speed = (destination - pos).Normalizar() * dt * 200;
				Vec2 nPos = pos + speed;
				if (nPos.Dist(destination) < 10.0){
					nPos.x = destination.x;
					nPos.y = destination.y;

					Vec2 p = PenguinBody::player->GetPos();
					auto m = std::min_element(minionArray.begin(), minionArray.end(), [p](auto x, auto y) mutable {return x.lock()->box.GetCenter().Dist(p) < y.lock()->box.GetCenter().Dist(p);});
					((Minion*)(*m).lock()->GetComponent("Minion"))->Shoot(p);
					restTimer.Restart();
					state = RESTING;
				}
				associated.box.SetCenter(nPos);
				break;
		}
	}

	if (hp <= 0){
		associated.RequestDelete();
		auto* go = new GameObject();
		auto* sprite = new Sprite(*go, "Recursos/img/aliendeath.png", 4, 0.2, 4*0.2);
		go->AddComponent(sprite);
		auto* sound = new Sound(*go, "Recursos/audio/boom.wav");
		sound->Play();
		go->AddComponent(sound);
		go->box.SetCenter(associated.box.GetCenter());
		go->angleDeg = associated.angleDeg;
		Game::GetInstance().GetCurrentState().AddObject(go);
	}
	associated.angleDeg += 0.5;
}

void Alien::NotifyCollision(GameObject& other){
	auto bullet = (Bullet*) other.GetComponent("Bullet");
	if (bullet && !bullet->targetsPlayer){
		hp -= bullet->GetDamage();
	}
}

bool Alien::Is(std::string type){
	return type == "Alien";
}
