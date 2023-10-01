#include "SDL2/SDL.h"

#include <cmath>
#include <ctime>
#include <string>
#include <iostream>

#include "State.h"
#include "Sound.h"
#include "Face.h"
#include "Sprite.h"
#include "TileMap.h"
#include "TileSet.h"
#include "InputManager.h"
#include "Camera.h"
#include "CameraFollower.h"

State::State(){
	quitRequested = false;
	LoadAssets();
}

void State::LoadAssets(){
	GameObject* go = new GameObject();
	Sprite* bg = new Sprite(*go, "Recursos/img/ocean.jpg");
	go->AddComponent(bg);
	CameraFollower* cf = new CameraFollower(*go);
	go->AddComponent(cf);
	objectArray.emplace_back(go);
	music.Open("Recursos/audio/stageState.ogg");
	music.Play();

	GameObject* go2 = new GameObject();
	TileSet* ts = new TileSet(64, 64, "Recursos/img/tileset.png");
	TileMap* tm = new TileMap(*go2, "Recursos/map/tileMap.txt", ts);
	go2->AddComponent(tm);
	go2->box.x = 0;
	go2->box.y = 0;
	objectArray.emplace_back(go2);
}

void State::Update(float dt){
	InputManager& im = InputManager::GetInstance();
	if (im.KeyPress(ESCAPE_KEY) || im.QuitRequested())
		quitRequested = true;

	if (im.IsKeyDown(SPACE_KEY)){
		Vec2 objPos = Vec2( 200, 0 ).GetRotated( -M_PI + M_PI*(rand() % 1001)/500.0 ) + Vec2( im.GetMouseX(), im.GetMouseY() );
		AddObject((int)objPos.x, (int)objPos.y);
	}

	Camera::Update(dt);

	for (int i=0; i < (int) objectArray.size(); i++){
		objectArray[i]->Update(dt);
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

void State::AddObject(int mouseX, int mouseY){
	GameObject* go = new GameObject();
	Sprite* sprite = new Sprite(*go, "Recursos/img/penguinface.png");
	go->AddComponent(sprite);
	go->box.x = mouseX - go->box.w/2 + Camera::pos.x;
	go->box.y = mouseY - go->box.h/2 + Camera::pos.y;
	Sound* sound = new Sound(*go, "Recursos/audio/boom.wav");
	go->AddComponent(sound);
	Face* face = new Face(*go);
	go->AddComponent(face);
	objectArray.emplace_back(go);
}
