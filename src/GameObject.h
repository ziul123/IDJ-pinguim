#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <memory>
#include <vector>

#include "Geometria.h"

class Component;

class GameObject {
	public:
		GameObject();
		~GameObject();
		void Update(float dt);
		void Render();
		bool IsDead() {return isDead;};
		void RequestDelete() {isDead=true;};
		void AddComponent(Component* cpt);
		void RemoveComponent(Component* cpt);
		Component* GetComponent(std::string type);
		void Start();
		void NotifyCollision(GameObject& other);
		Rect box;
		bool started;
		double angleDeg;

	private:
		std::vector<std::unique_ptr<Component>> components;
		bool isDead;
};

#endif
