#include "TitleState.h"

#include "GameObject.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "StageState.h"
#include "Camera.h"
#include "Text.h"
#include "Colors.h"
#include "Blinker.h"
#include "utils.h"

TitleState::TitleState(): State(){
}

void TitleState::Start(){
	LoadAssets();
	started = true;
}

void TitleState::LoadAssets(){
	{
	auto* go = new GameObject();
	auto* s = new Sprite(*go, "Recursos/img/title.jpg");
	go->AddComponent(s);
	AddObject(go);
	}
	{
	GameObject* go = new GameObject();
	auto* text = new Text(*go, "Recursos/font/Cmm.ttf", 70, Text::BLENDED, "Aperte espaco para continuar", colorFromHex("#ff5f03"));
	go->AddComponent(text);
	auto* blinker = new Blinker(*go, 0.3);
	go->AddComponent(blinker);
	go->box.SetCenter(Vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT-70));
	AddObject(go);
	}
}

void TitleState::Update(float dt){
	Camera::pos = Vec2(0,0);
	InputManager& im = InputManager::GetInstance();
	if (im.KeyPress(ESCAPE_KEY) || im.QuitRequested())
		quitRequested = true;

	if (im.KeyPress(SPACE_KEY)){
		Game::GetInstance().Push(new StageState());
		popRequested = true;
	}

	UpdateArray(dt);
	
}

