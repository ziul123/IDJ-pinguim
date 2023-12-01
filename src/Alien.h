#ifndef ALIEN_H
#define ALIEN_H

#include <queue>
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <ctime>
#include <random>

#include "Component.h"
#include "GameObject.h"
#include "Geometria.h"
#include "Timer.h"

class Alien: public Component {
	public:
		Alien(GameObject& associated, int nMinions);
		~Alien();
		void Start() override;
		void Update(float dt) override;
		void Render() override {};
		bool Is(std::string type) override;
		void NotifyCollision(GameObject& other) override;
		static int alienCount;
		int GetHp() {return hp;};

	private:
		Vec2 speed;
		int hp;
		int nMinions;
		std::vector<std::weak_ptr<GameObject>> minionArray;
		enum AlienState { MOVING, RESTING};
		AlienState state;
		Timer restTimer;
		Vec2 destination;
		float timeOffset;
		std::uniform_real_distribution<> rng;
		std::mt19937 gen;

};

#endif
