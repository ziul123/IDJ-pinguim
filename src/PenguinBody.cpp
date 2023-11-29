#include "PenguinBody.h"

#include <algorithm>
#include <memory>

#include "Component.h"
#include "InputManager.h"
#include "GameObject.h"
#include "Game.h"
#include "Geometria.h"
#include "PenguinCannon.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Collider.h"
#include "Camera.h"
#include "Sound.h"
#include "utils.h"

PenguinBody::PenguinBody(GameObject& associated): Component(associated){
	speed = Vec2(1, 1);
	linearSpeed = 1;
	angle = 0;
	hp = 100;
	player = this;
	Sprite* s = new Sprite(associated, "Recursos/img/penguin.png");
	associated.AddComponent(s);
	Collider* col = new Collider(associated);
	associated.AddComponent(col);
}

PenguinBody::~PenguinBody(){
	player = nullptr;
}

void PenguinBody::Start(){
	auto& state = Game::GetInstance().GetState();
	auto* go = new GameObject();
	go->AddComponent(new PenguinCannon(*go, state.GetObjectPtr(&associated)));
	pcannon = state.AddObject(go);
}

void PenguinBody::Update(float dt){
	auto& input = InputManager::GetInstance();

	if (input.IsKeyDown(W_KEY)) {
        linearSpeed = std::min(linearSpeed + 1000.0f * dt, +400.0f);
    }
    if (input.IsKeyDown(S_KEY)) {
        linearSpeed = std::max(linearSpeed - 1000.0f * dt, -400.0f);
    }

    float sign = linearSpeed >= 0 ? 1 : -1;
    if (input.IsKeyDown(A_KEY)) {
        angle += 3 * dt * sign;
    }
    if (input.IsKeyDown(D_KEY)) {
        angle -= 3 * dt * sign;
    }

	speed = Vec2(linearSpeed, 0).GetRotated(angle);

    associated.box.x += speed.x * dt;
    associated.box.y += speed.y * dt;

    associated.angleDeg = -angle*180/PI;
	if (hp <= 0){
		Camera::Unfollow();
		associated.RequestDelete();
		pcannon.lock()->RequestDelete();
		auto* go = new GameObject();
		auto* sprite = new Sprite(*go, "Recursos/img/penguindeath.png", 5, 0.2, 5*0.2);
		go->AddComponent(sprite);
		auto* sound = new Sound(*go, "Recursos/audio/boom.wav");
		sound->Play();
		go->AddComponent(sound);
		go->box.SetCenter(associated.box.GetCenter());
		Game::GetInstance().GetState().AddObject(go);
	}
}

void PenguinBody::NotifyCollision(GameObject& other){
	auto bullet = (Bullet*) other.GetComponent("Bullet");
	if (bullet && bullet->targetsPlayer) {
		hp -= bullet->GetDamage();
	}
}

bool PenguinBody::Is(std::string type){
	return type == "PenguinBody";
}
