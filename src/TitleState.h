#ifndef TITLE_STATE_H
#define TITLE_STATE_H

#include "State.h"

class TitleState: public State {
	public:
		TitleState();
		~TitleState() {};

		void Update(float dt);
		void Render();

};

#endif
