//
// Created by bvasseur on 1/5/25.
//

#ifndef PARTICLE_H
#define PARTICLE_H

# include <iostream>
# include <SFML/Graphics.hpp>
# include <random>

class Particle {
public:
	Particle();
	Particle(
		sf::Vector2f	position,
		sf::Color		color,
		sf::Vector2f	minMaxSize,
		sf::Vector2f	minMaxSpeed,
		float			direction,
		float			spread,
		sf::Time		lifetime = sf::seconds(1),
		sf::Vector2f	drift = {0, 0},
		float			sizeModifier = 0,
		float			speedModifier = 0,
		float			noiseForce = 0,
		bool			shouldRespawn = false);
	~Particle();
	Particle(const Particle &src);
	Particle &operator=(const Particle &src);

	bool			shouldRespawn() const;
	bool			isAlive() const;
	sf::Vector2f	getPosition() const;
	sf::Color		getColor() const;

	void update(sf::Time elapsed);

private:
	sf::Vector2f		_position;
	sf::Color			_color; // RGBA
	sf::Vector2f		_minMaxSize; // x: min, y: max size
	sf::Vector2f		_minMaxSpeed; // x: min, y: max speed
	float				_direction; // angle
	float				_spread; // angle, includes both sides ex : 20° -> 40°
	sf::Time			_lifetime; // in seconds
	sf::Vector2f		_drift; // each frame drift on x and y
	float				_sizeModifier; // each frame changes size
	float				_speedModifier; // each frame changes speed
	float				_noiseForce; // random force
	bool				_shouldRespawn = false;
	bool				_alive = true;

	float				_size;
	float				_speed;
	sf::Vector2f		_directionVector;
	sf::Vector2f		_velocity;
};



#endif //PARTICLE_H
