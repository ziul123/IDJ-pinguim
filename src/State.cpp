#include "SDL2/SDL.h"

#include <cmath>
#include <ctime>
#include <string>
#include <iostream>

#include "State.h"
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

State::State(){
	quitRequested = false;
	started = false;
}

void State::Start(){
	LoadAssets();
	for (int i = 0; i < (int) objectArray.size(); i++)
		objectArray[i]->Start();
	started = true;
}

void State::LoadAssets(){
	GameObject* go = new GameObject();
	Sprite* bg = new Sprite(*go, "Recursos/img/ocean.jpg");
	go->AddComponent(bg);
	CameraFollower* cf = new CameraFollower(*go);
	go->AddComponent(cf);
	AddObject(go);
	music.Open("Recursos/audio/stageState.ogg");
	music.Play();

	GameObject* go2 = new GameObject();
	TileSet* ts = new TileSet(64, 64, "Recursos/img/tileset.png");
	TileMap* tm = new TileMap(*go2, "Recursos/map/tileMap.txt", ts);
	go2->AddComponent(tm);
	go2->box.x = 0;
	go2->box.y = 0;
	AddObject(go2);

	GameObject* go3 = new GameObject();
	Alien* a = new Alien(*go3, 4);
	go3->AddComponent(a);
	go3->box.SetCenter(Vec2(512.0, 300.0));
	AddObject(go3);

	auto go4 = new GameObject();
	auto p = new PenguinBody(*go4);
	go4->AddComponent(p);
	go4->box.SetCenter(Vec2(704, 640));
	AddObject(go4);
}

void State::Update(float dt){
	InputManager& im = InputManager::GetInstance();
	if (im.KeyPress(ESCAPE_KEY) || im.QuitRequested())
		quitRequested = true;

	std::vector<GameObject*> collidables;

	Camera::Update(dt);

	for (int i=0; i < (int) objectArray.size(); i++){
		objectArray[i]->Update(dt);
		if (objectArray[i]->GetComponent("Collider"))
			collidables.push_back(objectArray[i].get());
	}
	for (int i=0; i < (int) collidables.size() - 1; i++){
		for (int j=i+1; j < (int) collidables.size(); j++){
			auto go1 = collidables[i];
			auto go2 = collidables[j];
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

void State::Render(){
	for (int i = 0; i < (int) objectArray.size(); i++)
		objectArray[i]->Render();
}

State::~State(){
	objectArray.clear();
}


std::weak_ptr<GameObject> State::AddObject(GameObject* go){
	std::shared_ptr<GameObject> p{ go };
	objectArray.push_back(p);
	if (started)
		p->Start();

	std::weak_ptr<GameObject> w(p);
	return w;
}

std::weak_ptr<GameObject> State::GetObjectPtr(GameObject* go){
	std::weak_ptr<GameObject> w;
	for (int i = 0; i < (int) objectArray.size(); i++){
		if (objectArray[i].get() == go)
			w = objectArray[i];
	}
	return w;
}
