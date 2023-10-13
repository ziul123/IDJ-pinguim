#ifndef MINION_H
#define MINION_H

#include <memory>
#include <string>

#include "Component.h"
#include "GameObject.h"
#include "Geometria.h"

class Minion: public Component{
	public:
		Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
		void Update(float dt) override;
		void Render() override {};
		bool Is(std::string type) override;
		void Shoot(Vec2 target);

	private:
		std::weak_ptr<GameObject> alienCenter;
		float arc;
};

#endif
