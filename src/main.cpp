#include "Game.h"
#include "Resources.h"

int main(int arg, char **argv){
	Game game = Game::GetInstance();
	game.Run();
	Resources::ClearImages();
	Resources::ClearMusics();
	Resources::ClearSounds();
}
