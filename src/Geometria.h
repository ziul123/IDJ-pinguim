#ifndef GEOMETRIA_H
#define GEOMETRIA_H

class Vec2;

class Rect {
	public:
		Rect(){x=0;y=0;w=0;h=0;};
		Rect(float x, float y, float w, float h){this->x=x;this->y=y;this->w=w;this->h=h;};
		float x, y, w, h;

		Vec2 GetCenter();
		void operator=(Rect const& r){x=r.x;y=r.y;w=r.w;h=r.h;};
		bool Contains(Vec2 v);
		
};


class Vec2 {
	public:
		Vec2(){x=0;y=0;};
		Vec2(float x, float y){this->x=x;this->y=y;};
		float x, y;

		Vec2 operator+(Vec2 const& v);
		Vec2 operator-(Vec2 const& v);
		Vec2 operator*(float f);
		float Magnitude();
		Vec2 Normalizar();
		float Dist(Vec2 const& v);
		void operator=(Vec2 const& v){x=v.x;y=v.y;};
		float Incline();
		Vec2 GetRotated(float angle);
};


#endif
