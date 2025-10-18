#pragma once

#include "Particle.hpp"
#include <vector>

class Simulation {
private:
	std::vector<Particle> particles;
	sf::Vector2f gravity;

public:
	Simulation();

	void addParticle(sf::Vector2f& position);
	void update(float dt, const sf::Vector2u& windowSize);
	void draw(sf::RenderWindow& window);
};