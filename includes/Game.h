#ifndef GAME_H
#define GAME_H

# include <iostream>

class Game {
public:
	Game();
	~Game();
	Game(const Game &src);
	Game &operator=(const Game &src);

	void run();

private:
};



#endif //GAME_H
