#pragma once

#include <SFML/Graphics.hpp>

class Particle {
public:
	sf::Vector2f position;
	sf::Vector2f prevPosition;
	sf::Vector2f acceleration;
	float radius;

	Particle(sf::Vector2f& startPos, const float r = 8.f);

	void applyForce(const sf::Vector2f& force);
	void update(float dt);
	void constraintToWindow(const sf::Vector2u& windowSize);
	void draw(sf::RenderWindow& window);
};