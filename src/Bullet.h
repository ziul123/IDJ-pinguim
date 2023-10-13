#ifndef BULLET_H
#define BULLET_H

#include <string>

#include "Component.h"
#include "GameObject.h"

class Bullet: public Component{
	public:
		Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite);
		void Update(float dt) override;
		void Render() override {};
		bool Is(std::string type) override;
		int GetDamage() {return damage;};

	private:
		Vec2 speed;
		float distanceLeft;
		int damage;
};

#endif
