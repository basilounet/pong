//
// Created by bvasseur on 1/5/25.
//

#include "Particle.h"

Particle::Particle() :
		_position({0, 0}),
		_color(0),
		_minMaxSize({0, 0}),
		_minMaxSpeed({0, 0}),
		_direction(0),
		_spread(0),
		_lifetime(sf::seconds(0)),
		_drift({0, 0}),
		_sizeModifier(0),
		_speedModifier(0),
		_noiseForce(0),
		_shouldRespawn(false),
		_alive(false),
		_size(0),
		_speed(0),
		_directionVector({0, 0}),
		_velocity({0, 0}) {
}

Particle::Particle(
	sf::Vector2f startPosition,
	sf::Color color,
	sf::Vector2f minMaxSize,
	sf::Vector2f minMaxSpeed,
	float direction,
	float spread,
	sf::Time lifetime,
	sf::Vector2f drift,
	float sizeModifier,
	float speedModifier,
	float noiseForce,
	bool shouldRespawn) :
		_position(startPosition),
		_color(color),
		_minMaxSize(minMaxSize),
		_minMaxSpeed(minMaxSpeed),
		_direction(direction),
		_spread(spread),
		_lifetime(lifetime),
		_drift(drift),
		_sizeModifier(sizeModifier),
		_speedModifier(speedModifier),
		_noiseForce(noiseForce),
		_shouldRespawn(shouldRespawn),
		_alive(true) {

	static std::random_device rd;
	static std::mt19937       rng(rd());

	_size = std::uniform_real_distribution(_minMaxSize.y, _minMaxSize.x)(rng);
	_speed = std::uniform_real_distribution(_minMaxSpeed.y, _minMaxSpeed.x)(rng);
	_directionVector = sf::Vector2f(1, 0).rotatedBy(sf::degrees(
		static_cast<int>(std::uniform_real_distribution(_direction - _spread, _direction + _spread)(rng))));
	_velocity = _directionVector * _speed;
}

Particle::~Particle() {}

Particle::Particle(const Particle& src) {
	*this = src;
}

Particle& Particle::operator=(const Particle& src)
{
	if (this != &src)
	{
		_position = src._position;
		_color = src._color;
		_minMaxSize = src._minMaxSize;
		_direction = src._direction;
		_spread = src._spread;
		_lifetime = src._lifetime;
		_drift = src._drift;
		_sizeModifier = src._sizeModifier;
		_speedModifier = src._speedModifier;
		_noiseForce = src._noiseForce;
		_shouldRespawn = src._shouldRespawn;
		_alive = src._alive;
		_size = src._size;
		_speed = src._speed;
		_directionVector = src._directionVector;
		_velocity = src._velocity;
	}
	return (*this);
}

bool Particle::shouldRespawn() const { return (_shouldRespawn); }

bool Particle::isAlive() const { return (_alive); }

sf::Vector2f Particle::getPosition() const { return (_position); }

sf::Color Particle::getColor() const { return (_color); }

void Particle::update(sf::Time elapsed) {
	_lifetime -= elapsed;

	// if the particle is dead, respawn it
	if (_lifetime <= sf::Time::Zero)
	{
		_alive = false;
		return ;
	}
	// std::cout << "velocity: [" << _velocity.x << ", " << _velocity.y << "]" << std::endl;
	sf::Vector2f	vec_noise = sf::Vector2f(1,0).rotatedBy(sf::degrees((rand() % 20001 - 10000) / 10000.f * 360));
	_velocity += (vec_noise * _noiseForce);
	_position.x += _velocity.x * elapsed.asSeconds() + _drift.x;
	_position.y += _velocity.y * elapsed.asSeconds() + _drift.y;
	_speed += _speedModifier;
	_size += _sizeModifier;
	_velocity = _directionVector * _speed;
}
