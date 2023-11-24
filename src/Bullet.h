#ifndef BULLET_H
#define BULLET_H

#include <string>

#include "Component.h"
#include "GameObject.h"

class Bullet: public Component{
	public:
		Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite, int frameCount, float frameTime, bool tp);
		void Update(float dt) override;
		void Render() override {};
		bool Is(std::string type) override;
		int GetDamage() {return damage;};
		void NotifyCollision(GameObject& other) override;
		bool targetsPlayer;

	private:
		Vec2 speed;
		float distanceLeft;
		int damage;
};

#endif
