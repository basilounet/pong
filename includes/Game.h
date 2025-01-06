#ifndef GAME_H
#define GAME_H

# include <iostream>
# include <SFML/Graphics.hpp>
# include <SFML/Window/Event.hpp>
# include <Colors.h>
# include <stdlib.h>
# include <math.h>
# include <vector>
# include <algorithm>
# include <ParticleSystem.h>

class Game {
public:
	Game();
	~Game();

	void initGame();
	void run();

private:
	sf::RenderWindow			_window;
	sf::RectangleShape			_rectangle;
	sf::CircleShape				_ball;
	sf::Clock					_clock;
	std::vector<ParticleSystem>	_particlesEffects;
	sf::Time					_dt; // delta time

	float			_recHeight = 100;
	float			_recWidth = 10;
	float			_moveSpeed = 300;
	float			_ballSize = 10.f;
	float			_ballSpeed = 300;

	static constexpr unsigned int WIDTH = 800;
	static constexpr unsigned int HEIGHT = 600;

	Game(const Game &src);
	Game &operator=(const Game &src);


	void checkEvents();
	void checkInputs();
	void MoveBall();
};



#endif //GAME_H
