#ifndef STAGE_STATE_H
#define STAGE_STATE_H

#include <memory>
#include <vector>

#include "Music.h"
#include "Sprite.h"
#include "GameObject.h"
#include "TileSet.h"
#include "State.h"
#include "Timer.h"

class StageState: public State {
	public:
		StageState();
		~StageState() {};

		void LoadAssets();
		void Update(float dt);

		void Start();
		void Pause() {};
		void Resume() {};

	private:
		void AddAlien(float x, float y, int minions);
		TileSet* tileSet;
		Music bgm;
		Timer endTimer;
		bool ended;
		
};

#endif
