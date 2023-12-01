#ifndef END_STATE_H
#define END_STATE_H

#include "State.h"
#include "Music.h"

class EndState: public State {
	public:
		EndState();
		~EndState() {};

		void LoadAssets();
		void Update(float dt);
		void Start();

	private:
		Music bgm;

};

#endif
