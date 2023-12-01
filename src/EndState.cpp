#include "EndState.h"

#include <string>

#include "Game.h"
#include "GameObject.h"
#include "GameData.h"
#include "Resources.h"
#include "Sprite.h"
#include "InputManager.h"
#include "Text.h"
#include "Blinker.h"
#include "Colors.h"
#include "Camera.h"
#include "TitleState.h"
#include "utils.h"

EndState::EndState(): State(){
}

void EndState::Start(){
	LoadAssets();
	started = true;
}

void EndState::LoadAssets(){
	{
	auto* go = new GameObject();
	std::string img;
	if (GameData::playerVictory) {
		bgm.Open("Recursos/audio/endStateWin.ogg");
		img = "Recursos/img/win.jpg";
	} else {
		bgm.Open("Recursos/audio/endStateLose.ogg");
		img = "Recursos/img/lose.jpg";
	}
	go->AddComponent(new Sprite(*go, img));
	AddObject(go);
	}
	{
	auto* go = new GameObject();
	auto* text = new Text(*go, "Recursos/font/Cmm.ttf", 50, Text::BLENDED, "Aperte esc para sair\nAperte espaco para jogar de novo", colorFromHex("#ff5f03"));
	go->AddComponent(text);
	auto* blinker = new Blinker(*go, 0.3);
	go->AddComponent(blinker);
	go->box.SetCenter(Vec2(SCREEN_WIDTH/2, SCREEN_HEIGHT-140));
	AddObject(go);
	}

	bgm.Play();
}

void EndState::Update(float dt){
	Camera::pos = Vec2(0,0);
	InputManager& im = InputManager::GetInstance();
	if (im.KeyPress(ESCAPE_KEY) || im.QuitRequested())
		quitRequested = true;

	if (im.KeyPress(SPACE_KEY)){
		popRequested = true;
		Game::GetInstance().Push(new TitleState());
	}

	UpdateArray(dt);
}
