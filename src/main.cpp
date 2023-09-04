#include "Game.h"

int main(int arg, char **argv){
	Game game = Game::getInstance();
	game.run();
}
