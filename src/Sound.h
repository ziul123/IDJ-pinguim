#ifndef SOUND_H
#define SOUND_H

#include "SDL2/SDL_mixer.h"

#include <string>

#include "Component.h"
#include "GameObject.h"

class Sound: public Component {
	public:
		Sound(GameObject& associated);
		Sound(GameObject& associated, std::string file);
		~Sound();
		void Play(int times = 1);
		void Stop();
		void Open(std::string file);
		bool IsOpen();
		void Update(float dt) override {};
		void Render() override {};
		bool Is(std::string type) override;
		bool IsPlaying();

	private:
		Mix_Chunk* chunk;
		int channel;
};

#endif
