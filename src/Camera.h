#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"
#include "Geometria.h"

class Camera {
	public:
		static void Follow(GameObject* newFocus){focus=newFocus;};
		static void Unfollow(){focus=nullptr;};
		static void Update(float dt);
		static Vec2 pos;
		static Vec2 speed;

	private:
		static GameObject* focus;

};

#endif
