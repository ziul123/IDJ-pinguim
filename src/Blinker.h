#ifndef BLINKER_H
#define BLINKER_H

#include "Component.h"
#include "Timer.h"

class Blinker: public Component {
	public:
		Blinker(GameObject& associated, float freq);
		void Update(float dt);
		float freq;
		bool Is(std::string type);

	private:
		Timer timer;
};

#endif
