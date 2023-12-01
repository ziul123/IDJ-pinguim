#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <memory>
#include <vector>

#include "Geometria.h"

class Component;

class GameObject {
	public:
		GameObject(bool render = true);
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
		void SetRender(bool render);
		Rect box;
		bool started;
		double angleDeg;
		bool render;

	private:
		std::vector<std::unique_ptr<Component>> components;
		bool isDead;
};

#endif
