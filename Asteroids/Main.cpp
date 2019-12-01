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
sf::ContextSettings settings;

sf::Font font;

sf::Sprite bg;

sf::Texture aircraftTex;
sf::Texture backgroundTex;

sf::SoundBuffer backgroundBuffer;
sf::Sound backgroundSound(backgroundBuffer);

sf::SoundBuffer thrustBuffer;



bool LoadResources() {
	if (!font.loadFromFile("resources/Font/sansation.ttf")) { return false; }

	if (!aircraftTex.loadFromFile("resources/Textures/aircraft_player.png")) { return false; }
	if (!backgroundTex.loadFromFile("resources/Textures/texture_background.jpg")) { return false; }
	
	if (!backgroundBuffer.loadFromFile("resources/Audio/music_background.wav")) { return false; }
	if (!thrustBuffer.loadFromFile("resources/Audio/thrust1.wav")) { return false; }
	return true;
}
void Setupbackground(){
	bg.setTexture(backgroundTex);


}

void Start() {

}
void LoadLevel() {

}

int main() {

	bool gameStart = false;
	bool loadLevel = false;

	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(winSize.x, winSize.y), "Asteroids", sf::Style::Default, settings);
	if (!LoadResources()) { return EXIT_FAILURE; }

	bg.setTexture(backgroundTex);
	
	Aircraft player;
	player.SetRadius(50);
	player.SetForce(100);
	player.SetHeading(270);
	player.SetRotateSpeed(240);
	player.setPosition(winSize / 2.f);
	player.SetTexture(aircraftTex);
	player.SetThrustSound(thrustBuffer);

	sf::Clock clock;
	backgroundSound.play();
	backgroundSound.setLoop(true);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}
		float deltaTime = clock.restart().asSeconds();

		if (!gameStart) {
			Start();
			gameStart = true;
		}
		if (!loadLevel) {

		}

		player.Update(deltaTime);

		window.clear();
		window.draw(bg);
		window.draw(player);
		window.display();
	}
	return EXIT_SUCCESS;
}