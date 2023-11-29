#ifdef DEBUG
#include "Camera.h"
#include "Game.h"
#include "utils.h"

#include <SDL2/SDL.h>
#endif // DEBUG

#include "Collider.h"

Collider::Collider(GameObject& associated, Vec2 s, Vec2 o): Component(associated){
	scale = s;
	offset = o;
}

void Collider::Update(float dt){
	box.x = associated.box.x;
	box.y = associated.box.y;
	box.w = associated.box.w * scale.x;
	box.h = associated.box.h * scale.y;
	box.SetCenter(associated.box.GetCenter() + offset * associated.angleDeg);
}

void Collider::Render() {
#ifdef DEBUG
	Vec2 center( box.GetCenter() );
	SDL_Point points[5];

	Vec2 point = (Vec2(box.x, box.y) - center).GetRotated( -associated.angleDeg/(180/PI) )
					+ center - Camera::pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y) - center).GetRotated( -associated.angleDeg/(180/PI) )
					+ center - Camera::pos;
	points[1] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y + box.h) - center).GetRotated( -associated.angleDeg/(180/PI) )
					+ center - Camera::pos;
	points[2] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x, box.y + box.h) - center).GetRotated( -associated.angleDeg/(180/PI) )
					+ center - Camera::pos;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}

bool Collider::Is(std::string type){
	return type == "Collider";
}

void Collider::SetScale(Vec2 s){
	scale = s;
}

void Collider::SetOffset(Vec2 o){
	offset = o;
}
