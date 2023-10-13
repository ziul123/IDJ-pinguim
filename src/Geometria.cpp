#include <cmath>

#include "Geometria.h"

/*------Rect------*/

Vec2 Rect::GetCenter(){
	Vec2 res;
	res.x = x+w/2;
	res.y = y+h/2;
	return res;
}

bool Rect::Contains(Vec2 v){
	return (v.x >= x) && (v.x <= x+w) && (v.y >= y) && (v.y <= y+h);
}

void Rect::SetCenter(Vec2 v){
	x = v.x - w/2;
	y = v.y - h/2;
}

Rect Rect::operator+(Vec2 const& v){
	Rect r;
	r.x = x + v.x;
	r.y = y + v.y;
	r.w = w;
	r.h = h;
	return r;
}

/*------Vec2------*/

Vec2 Vec2::operator+(Vec2 const& v){
	Vec2 res;
	res.x = x+v.x;
	res.y = y+v.y;
	return res;
}

Vec2 Vec2::operator-(Vec2 const& v){
	Vec2 res;
	res.x = x-v.x;
	res.y = y-v.y;
	return res;
}

Vec2 Vec2::operator*(float f){
	Vec2 res;
	res.x = x*f;
	res.y = y*f;
	return res;
}

float Vec2::Magnitude(){
	return sqrt(pow(x, 2) + pow(y, 2));
}

Vec2 Vec2::Normalizar(){
	Vec2 res;
	float m = this->Magnitude();
	res.x = x/m;
	res.y = y/m;
	return res;
}

float Vec2::Dist(Vec2 const& v){
	Vec2 x = *this - v;
	return x.Magnitude();
}

float Vec2::Incline(){
	return std::atan2(y, x);
}

float Vec2::Incline(Vec2 const& v){
	Vec2 x = *this - v;
	return x.Incline();
}

Vec2 Vec2::GetRotated(float angle){
	Vec2 result;
	float s = std::sin(angle);
	float c = std::cos(angle);
	result.x = x * c + y * s;
	result.y = y * c - x * s;
	return result;
}
