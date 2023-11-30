#include "Game.h"
#include "TitleState.h"

int main(int arg, char **argv){
	Game& game = Game::GetInstance();
	auto* title = new TitleState();
	game.Push(title);
	game.Run();
}
