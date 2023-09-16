#ifndef FACE_H
#define FACE_H

#include <string>

#include "Component.h"
#include "GameObject.h"

class Face: public Component{
	public:
		Face(GameObject& associated, int hp = 30);
		void Damage(int damage);
		void Update(float dt) override;
		void Render() override {};
		bool Is(std::string type) override;

	private:
		int hitpoints;
};

#endif
