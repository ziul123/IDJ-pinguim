#ifndef ALIEN_H
#define ALIEN_H

#include <queue>
#include <string>
#include <memory>
#include <vector>
#include <iostream>
#include <ctime>

#include "Component.h"
#include "GameObject.h"
#include "Geometria.h"

class Alien: public Component {
	public:
		Alien(GameObject& associated, int nMinions);
		~Alien();
		void Start() override;
		void Update(float dt) override;
		void Render() override {};
		bool Is(std::string type) override;
		void NotifyCollision(GameObject& other) override;

	private:
		class Action {
			public:
				enum ActionType {MOVE, SHOOT};
				Action(ActionType type, float x, float y){
					this->type = type;
					pos.x = x;
					pos.y = y;
				};
				ActionType type;
				Vec2 pos;
		};
		Vec2 speed;
		int hp;
		int nMinions;
		std::queue<Action> taskQueue;
		std::vector<std::weak_ptr<GameObject>> minionArray;

};

#endif
