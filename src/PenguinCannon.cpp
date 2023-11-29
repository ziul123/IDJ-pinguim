#include "PenguinCannon.h"

#include <memory>

#include "Component.h"
#include "Camera.h"
#include "GameObject.h"
#include "Game.h"
#include "Geometria.h"
#include "InputManager.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Collider.h"
#include "utils.h"

PenguinCannon::PenguinCannon(GameObject& associated, std::weak_ptr<GameObject> penguinBody): Component(associated){
	angle = 0;
	pbody = penguinBody;
	Sprite* s = new Sprite(associated, "Recursos/img/cubngun.png");
	associated.AddComponent(s);
	Collider* col = new Collider(associated);
	associated.AddComponent(col);
}

void PenguinCannon::Update(float dt){
	if (pbody.expired()){
		associated.RequestDelete();
		return;
	}
	auto center = pbody.lock()->box.GetCenter();
	associated.box.SetCenter(center);
	float cX = Camera::pos.x;
	float cY = Camera::pos.y;
	auto& input = InputManager::GetInstance();

	auto mouse = Vec2((float)input.GetMouseX()+cX, (float)input.GetMouseY()+cY);
	angle = mouse.Incline(center);

	associated.angleDeg = angle*180/PI;
	cooldown.Update(dt);

    if (input.MousePress(LEFT_MOUSE_BUTTON) && cooldown.Get() >= 0.5) {
        Shoot();
		cooldown.Restart();
    }

}

void PenguinCannon::Shoot(){
	auto* go = new GameObject();
	auto* bullet = new Bullet(*go, angle, 200.0, 20, 1000.0, "Recursos/img/minionbullet2.png", 3, 0.3, false);
	go->AddComponent(bullet);
	
	Vec2 distanceOffset = Vec2(60, 0).GetRotated(-angle);
    go->box.SetCenter(associated.box.GetCenter() + distanceOffset);

	Game::GetInstance().GetState().AddObject(go);
}

bool PenguinCannon::Is(std::string type){
	return type == "PenguinCannon";
}
