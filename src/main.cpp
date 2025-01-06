#include <SFML/Graphics.hpp>
#include <Game.h>

int main()
{
	Game game;
	srand(time(nullptr));
	try {
		game.initGame();
		game.run();
	}
	catch (const std::exception& e) {
        std::cerr << RED << "Error while ponging : " << e.what() << BASE_COLOR << std::endl;
    }
	return 0;
}
