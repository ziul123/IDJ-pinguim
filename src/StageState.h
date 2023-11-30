#ifndef STAGE_STATE_H
#define STAGE_STATE_H

#include <memory>
#include <vector>

#include "Music.h"
#include "Sprite.h"
#include "GameObject.h"
#include "TileSet.h"
#include "State.h"

class StageState: public State {
	public:
		StageState();
		~StageState() {};

		void LoadAssets();
		void Update(float dt);
		void Render();

		void Start();
		void Pause() {};
		void Resume() {};

	private:
		TileSet* tileSet;
		Music bgm;
		
};

#endif
