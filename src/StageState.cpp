#include "SDL2/SDL.h"

#include <cmath>
#include <ctime>
#include <string>
#include <iostream>

#include "StageState.h"
#include "Sound.h"
#include "Sprite.h"
#include "TileMap.h"
#include "TileSet.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"
#include "Alien.h"
#include "PenguinBody.h"
#include "Collision.cpp"
#include "Collider.h"
#include "utils.h"

StageState::StageState(): State(){}

void StageState::Start(){
	LoadAssets();
	StartArray();
	started = true;
}

void StageState::LoadAssets(){
	GameObject* go = new GameObject();
	Sprite* bg = new Sprite(*go, "Recursos/img/ocean.jpg");
	go->AddComponent(bg);
	CameraFollower* cf = new CameraFollower(*go);
	go->AddComponent(cf);
	AddObject(go);
	bgm.Open("Recursos/audio/stageState.ogg");
	bgm.Play();

	GameObject* go2 = new GameObject();
	tileSet = new TileSet(64, 64, "Recursos/img/tileset.png");
	TileMap* tm = new TileMap(*go2, "Recursos/map/tileMap.txt", tileSet);
	go2->AddComponent(tm);
	go2->box.x = 0;
	go2->box.y = 0;
	AddObject(go2);

	GameObject* go3 = new GameObject();
	Alien* a = new Alien(*go3, 4);
	go3->AddComponent(a);
	go3->box.SetCenter(Vec2(512.0, 300.0));
	AddObject(go3);

	auto* go4 = new GameObject();
	auto* p = new PenguinBody(*go4);
	go4->AddComponent(p);
	go4->box.SetCenter(Vec2(704, 640));
	AddObject(go4);
	Camera::Follow(go4);

}

void StageState::Update(float dt){
	InputManager& im = InputManager::GetInstance();
	if (im.KeyPress(ESCAPE_KEY) || im.QuitRequested())
		popRequested = true;

	std::vector<GameObject*> collidables;

	Camera::Update(dt);

	for (int i=0; i < (int) objectArray.size(); i++){
		objectArray[i]->Update(dt);
		if (objectArray[i]->GetComponent("Collider"))
			collidables.push_back(objectArray[i].get());
	}

	for (int i=0; i < (int) collidables.size() - 1; i++){
		for (int j=i+1; j < (int) collidables.size(); j++){
			auto* go1 = collidables[i];
			auto* go2 = collidables[j];
			bool r = Collision::IsColliding(((Collider*)go1->GetComponent("Collider"))->box, ((Collider*)go2->GetComponent("Collider"))->box, go1->angleDeg * PI/180, go2->angleDeg * PI/180);
			if (r){
				go1->NotifyCollision(*go2);
				go2->NotifyCollision(*go1);
			}
		}
	}

	for (int i=0; i < (int) objectArray.size(); i++){
		if (objectArray[i]->IsDead())
			objectArray.erase(objectArray.begin()+i);
	}
}

void StageState::Render(){
	RenderArray();
}

