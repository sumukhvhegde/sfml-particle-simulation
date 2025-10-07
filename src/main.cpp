#include <SFML/Graphics.hpp>
#include "Simulation.hpp"

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

int main() {
	sf::RenderWindow window(sf::VideoMode({ WIDTH, HEIGHT }), "Particle Simulation", sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);

	Simulation sim;
	sf::Clock clock;

	while (window.isOpen()) {
		while (std::optional event = window.pollEvent()) {
			if (event->is<sf::Event::Closed>() || sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Escape)) {
				window.close();
			}
			else if (auto* e = event->getIf<sf::Event::MouseButtonPressed>()) {
				if (e->button == sf::Mouse::Button::Left) {
					sim.addParticle({ (float)e->position.x, (float)e->position.y });
				}
			}
		}

		float dt = clock.restart().asSeconds();
		if (dt > 0.016f) dt = 0.016f;

		sim.update(dt, window.getSize());

		window.clear();

		sim.draw(window);

		window.display();
	}

	return 0;
}