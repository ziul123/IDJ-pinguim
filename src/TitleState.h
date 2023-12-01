#ifndef TITLE_STATE_H
#define TITLE_STATE_H

#include "State.h"

class TitleState: public State {
	public:
		TitleState();
		~TitleState() {};

		void LoadAssets();
		void Update(float dt);
		void Start();

};

#endif
