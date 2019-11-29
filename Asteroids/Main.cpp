#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#include <iostream>

#include "Aircraft.h"

sf::RenderWindow window(sf::VideoMode(1366, 768), "Asteroids");
sf::Texture aircraftTex;


bool LoadResources() {
	if (!aircraftTex.loadFromFile("resources/Aircraft.png")) { return false; }
	return true;
}

int main() {
	if (!LoadResources()) { return EXIT_FAILURE; }
	
	Aircraft player;
	player.SetRadius(50);
	player.SetSpeed(400);
	player.SetRotateSpeed(120);
	player.setPosition(100, 100);
	player.SetTexture(aircraftTex);

	sf::Clock clock;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		float deltaTime = clock.restart().asSeconds();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
			player.RotateLeft(deltaTime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
			player.RotateRight(deltaTime);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
			player.Move(deltaTime);
		}

		float d = player.GetDirection();
		std::cout << cos(d * 3.14 / 180) <<  ", " << sin(d * 3.14 / 180) << "\n";
		window.clear();
		window.draw(player);
		window.display();
	}
	return EXIT_SUCCESS;
}