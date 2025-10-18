#include "Particle.hpp"

Particle::Particle(sf::Vector2f& startPos, const float r)
	: position(startPos),
	prevPosition(startPos),
	acceleration({0.f, 0.f}),
	radius(r) {}

void Particle::applyForce(const sf::Vector2f& force) {
	acceleration += force;
}

void Particle::update(float dt) {
	sf::Vector2f temp = position;
	position += position - prevPosition + (acceleration * dt * dt);
	prevPosition = temp;
	acceleration = { 0.f, 0.f };
}

void Particle::constraintToWindow(const sf::Vector2u& windowSize) {
	if (position.x < radius) position.x = radius;
	if (position.y < radius) position.y = radius;
	if (position.x > windowSize.x - radius) position.x = windowSize.x - radius;
	if (position.y > windowSize.y - radius) position.y = windowSize.y - radius;
}

void Particle::draw(sf::RenderWindow& window) {
	sf::CircleShape circle(radius);
	circle.setOrigin({ radius, radius });
	circle.setPosition(position);
	circle.setFillColor(sf::Color::White);
	
	window.draw(circle);
}