#include "Particle.hpp"

Particle::Particle(sf::Vector2f startPos, float r) : position(startPos), prevPosition(startPos), radius(r), acceleration({ 0.f, 0.f }), color(sf::Color::White) {}

void Particle::applyForce(const sf::Vector2f& force) {
	acceleration += force;
}

void Particle::update(float dt) {
	sf::Vector2f tempPosition = position;
	position += (position - prevPosition) + acceleration * (dt * dt);
	prevPosition = tempPosition;
	acceleration = { 0.f, 0.f };
}

void Particle::constrainToWindow(const sf::Vector2u& windowSize) {
	if (position.x < radius) position.x = radius;
	if (position.y < radius) position.y = radius;
	if (position.x > windowSize.x - radius) position.x = windowSize.x - radius;
	if (position.y > windowSize.y - radius) position.y = windowSize.y - radius;
}

void Particle::draw(sf::RenderWindow& window) {
	sf::CircleShape circle(radius);
	circle.setPosition({ position.x - radius, position.y - radius });
	circle.setFillColor(color);
	window.draw(circle);
}