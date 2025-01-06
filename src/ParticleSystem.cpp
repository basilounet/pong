//
// Created by bvasseur on 1/5/25.
//

#include <ParticleSystem.h>

ParticleSystem::ParticleSystem() :
	_amount(0),
	_startParticle(Particle()),
	_particles(),
	_vertices(sf::PrimitiveType::Points, 0) {
}

ParticleSystem::ParticleSystem(
	unsigned int amount,
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
		_amount(amount),
		_startParticle(Particle()),
		_particles(),
		_vertices(sf::PrimitiveType::Points, amount)
{
	_particles.reserve(amount);
	for (unsigned int i = 0; i < amount; i++) {
		Particle p(
			startPosition,
			color,
			minMaxSize,
			minMaxSpeed,
			direction,
			spread,
			lifetime,
			drift,
			sizeModifier,
			speedModifier,
			noiseForce,
			shouldRespawn
		);
		_particles.push_back(p);
	}
}

ParticleSystem::~ParticleSystem() {

}

ParticleSystem::ParticleSystem(const ParticleSystem& src) {
	*this = src;
}

ParticleSystem& ParticleSystem::operator=(const ParticleSystem& src)
{
	if (this != &src)
	{
		_amount = src._amount;
		_startParticle = src._startParticle;
		_particles = src._particles;
		_vertices = src._vertices;
	}
	return (*this);
}

void ParticleSystem::update(sf::Time elapsed) {
	for (std::size_t i = 0; i < _particles.size(); ++i)
	{
		Particle& p = _particles[i];
		if (!p.isAlive() && p.shouldRespawn())
			p = Particle(_startParticle);
		else if (!p.isAlive())
			continue ;
		p.update(elapsed);

		_vertices[i].position = p.getPosition();
		_vertices[i].color = p.getColor();
	}
}

void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	// apply the transform
	states.transform *= getTransform();

	// our particles don't use a texture
	states.texture = nullptr;

	// draw the vertex array
	target.draw(_vertices, states);
}

bool ParticleSystem::areAllParticlesDead() {
	for (std::size_t i = 0; i < _particles.size(); ++i) {
		if (_particles[i].isAlive())
			return (false);
	}
	_particles.clear();
	_vertices.clear();
	return (true);
}
