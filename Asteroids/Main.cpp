#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#include <iostream>

#include "Aircraft.h"
sf::Vector2f winSize(1366, 768);
sf::RenderWindow window(sf::VideoMode(winSize.x, winSize.y), "Asteroids");
sf::Texture aircraftTex;


bool LoadResources() {
	if (!aircraftTex.loadFromFile("resources/Aircraft.png")) { return false; }
	return true;
}

int main() {
	if (!LoadResources()) { return EXIT_FAILURE; }
	
	Aircraft player;
	player.SetRadius(50);
	player.SetForce(100);
	player.SetHeading(270);
	player.SetRotateSpeed(240);
	player.setPosition(winSize / 2.f);
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
			player.Accelerate(deltaTime);
		}

		player.Move(deltaTime);

		float d = player.GetHeading();
		std::cout << cos(d * 3.14 / 180) <<  ", " << sin(d * 3.14 / 180) << "\n";
		window.clear();
		window.draw(player);
		window.display();
	}
	return EXIT_SUCCESS;
}