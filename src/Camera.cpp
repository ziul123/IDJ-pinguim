#include "Camera.h"
#include "GameObject.h"
#include "Geometria.h"
#include "InputManager.h"

Vec2 Camera::pos = Vec2(0.0, 0.0);
Vec2 Camera::speed = Vec2(500.0, 500.0);
GameObject* Camera::focus = nullptr;

void Camera::Update(float dt){
	if (focus) {

	} else {
		InputManager& im = InputManager::GetInstance();
        if (im.IsKeyDown(RIGHT_ARROW_KEY)) pos.x += speed.x * dt;
        if (im.IsKeyDown(LEFT_ARROW_KEY)) pos.x -= speed.x * dt;
        if (im.IsKeyDown(DOWN_ARROW_KEY)) pos.y += speed.y * dt;
        if (im.IsKeyDown(UP_ARROW_KEY)) pos.y -= speed.y * dt;
	}
}
