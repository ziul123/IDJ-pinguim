#include "Camera.h"
#include "GameObject.h"
#include "Geometria.h"
#include "InputManager.h"
#include "utils.h"

Vec2 Camera::pos = Vec2(0.0, 0.0);
Vec2 Camera::speed = Vec2(500.0, 500.0);
GameObject* Camera::focus = nullptr;

void Camera::Update(float dt){
	if (focus) {
		auto center = focus->box.GetCenter();
		pos.x = center.x - SCREEN_WIDTH/2;
		pos.y = center.y - SCREEN_HEIGHT/2;

	} else {
		InputManager& im = InputManager::GetInstance();
        if (im.IsKeyDown(RIGHT_ARROW_KEY)) pos.x += speed.x * dt;
        if (im.IsKeyDown(LEFT_ARROW_KEY)) pos.x -= speed.x * dt;
        if (im.IsKeyDown(DOWN_ARROW_KEY)) pos.y += speed.y * dt;
        if (im.IsKeyDown(UP_ARROW_KEY)) pos.y -= speed.y * dt;
	}
}
