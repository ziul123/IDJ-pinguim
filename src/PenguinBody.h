#ifndef PENGUINBODY_H
#define PENGUINBODY_H

#include <string>
#include <memory>

#include "Component.h"
#include "GameObject.h"
#include "Geometria.h"

class PenguinBody: public Component{
	public:
		PenguinBody(GameObject& associated);
		~PenguinBody();

		void Start();
		void Update(float dt);
		void Render() {};
		bool Is(std::string type);
		void NotifyCollision(GameObject& other) override;
		Vec2 GetPos() {return associated.box.GetCenter();};

		inline static PenguinBody* player = nullptr;
	
	private:
		std::weak_ptr<GameObject> pcannon;
		Vec2 speed;
		float linearSpeed;
		float angle;
		int hp;

};

#endif
