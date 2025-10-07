#include "Simulation.hpp"

Simulation::Simulation() : gravity({ 0, 1000.f }) {}

void Simulation::addParticle(sf::Vector2f position) {
	particles.emplace_back(position);
}

void Simulation::update(float dt, const sf::Vector2u& windowSize) {
	for (auto& p : particles) {
		p.applyForce(gravity);
		p.update(dt);
		p.constrainToWindow(windowSize);

		for (size_t i = 0; i < particles.size(); ++i) {
			for (size_t j = i + 1; j < particles.size(); ++j) {
				sf::Vector2f delta = particles[j].position - particles[i].position;
				float dist = std::sqrt(delta.x * delta.x + delta.y * delta.y);
				float minDist = particles[i].radius + particles[j].radius;

				if (dist < minDist && dist > 0.f) {
					sf::Vector2f correction = (delta / dist) * (0.5f * (minDist - dist));
					particles[i].position -= correction;
					particles[j].position += correction;
				}
			}
		}
	}
}

void Simulation::draw(sf::RenderWindow& window) {
	for (auto& p : particles) {
		p.draw(window);
	}
}