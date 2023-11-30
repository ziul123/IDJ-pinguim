#include "TitleState.h"

#include "GameObject.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Game.h"
#include "StageState.h"
#include "Camera.h"

TitleState::TitleState(): State(){
	auto* go = new GameObject();
	auto* s = new Sprite(*go, "Recursos/img/title.jpg");
	go->AddComponent(s);
	AddObject(go);
}

void TitleState::Update(float dt){
	Camera::pos = Vec2(0,0);
	InputManager& im = InputManager::GetInstance();
	if (im.KeyPress(ESCAPE_KEY) || im.QuitRequested())
		quitRequested = true;

	if (im.KeyPress(SPACE_KEY))
		Game::GetInstance().Push(new StageState());
	
}

void TitleState::Render(){
	RenderArray();
}
