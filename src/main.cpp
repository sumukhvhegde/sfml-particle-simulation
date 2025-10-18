#include <SFML/Graphics.hpp>
#include <optional>

#include "Simulation.hpp"

constexpr unsigned int WIDTH = 1000;
constexpr unsigned int HEIGHT = 800;

constexpr unsigned int FRAME_RATE = 60;

int main() {
	sf::RenderWindow window(sf::VideoMode({ WIDTH, HEIGHT }), "Particle Simulation");
	window.setFramerateLimit(FRAME_RATE);

	Simulation sim;
	sf::Clock clk;

	while (window.isOpen()) {
		while (std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>()) {
				window.close();
			}
			else if (auto key = event->getIf<sf::Event::KeyPressed>()) {
				if (key->scancode == sf::Keyboard::Scan::Escape) {
					window.close();
				}
			}
			else if (auto* e = event->getIf<sf::Event::MouseButtonPressed>()) {
				if (e->button == sf::Mouse::Button::Left) {
					sf::Vector2f mousePos = { (float)e->position.x, (float)e->position.y };
					sim.addParticle(mousePos);
				}
			}
		}

		float dt = clk.restart().asSeconds();
		if (dt > 0.016f) dt = 0.016f;

		sim.update(dt, window.getSize());

		window.clear(sf::Color::Black);
		sim.draw(window);
		window.display();
	}

	return 0;
}