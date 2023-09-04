#ifndef STATE_H
#define STATE_H

#include "Music.h"
#include "Sprite.h"

class State{
	public:
		State();
		bool quitRequested();
		void loadAssets();
		void update(float dt);
		void render();

	private:
		Sprite bg;
		Music music;
		bool quit;
};

#endif
