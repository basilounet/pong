//
// Created by bvasseur on 1/5/25.
//

#ifndef PARTICLE_SYSTEM_H
#define PARTICLE_SYSTEM_H

# include <iostream>
# include <SFML/Graphics.hpp>
# include <vector>
# include <Particle.h>

class ParticleSystem : public sf::Drawable, sf::Transformable {
public:
	ParticleSystem();
	ParticleSystem(
		unsigned int	amount,
		sf::Vector2f	startPosition,
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
	~ParticleSystem() override;
	ParticleSystem(const ParticleSystem &src);
	ParticleSystem &operator=(const ParticleSystem &src);

	void	update(sf::Time elapsed);
	void	draw(sf::RenderTarget &target, sf::RenderStates states) const override;
	bool	areAllParticlesDead();

private:
	unsigned int			_amount;
	Particle                _startParticle;
	std::vector<Particle>	_particles;
	sf::VertexArray			_vertices;
};




#endif //PARTICLE_SYSTEM_H
