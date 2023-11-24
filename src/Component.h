#ifndef COMPONENT_H
#define COMPONENT_H

#include <string>

#include "GameObject.h"

class Component {
	public:
		Component(GameObject& associated);
		virtual ~Component(){};
		virtual void Update(float dt) {};
		virtual void Render() {};
		virtual bool Is(std::string type) = 0;
		virtual void Start() {};
		virtual void NotifyCollision(GameObject& other) {};

	protected:
		GameObject& associated;
};


#endif
