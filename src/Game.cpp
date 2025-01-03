#include <Game.h>

Game::Game() {
}

Game::~Game() {
}

Game::Game(const Game& src) {
	*this = src;
}

Game& Game::operator=(const Game& src)
{
	if (this != &src) {
	}
	return *this;
}

void Game::run() {
}
