#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#include <iostream>
#include <vector>

#include "GameState.h"
#include "Button.h"
#include "Aircraft.h"
#include "HealthBar.h"


sf::Vector2f winSize(1366, 768);
sf::ContextSettings settings;
GameState state;

sf::Font font;

sf::Sprite bg;

sf::Texture aircraftTex;
sf::Texture backgroundTex;
sf::Texture btnTex;
sf::Texture health;
sf::Texture healthBg;

sf::SoundBuffer bgmBuffer;
sf::Sound bgm(bgmBuffer);

sf::SoundBuffer thrustBuffer;

std::vector<Button*> menuBtnList;
Button startBtn;


bool LoadResources() {
	if (!font.loadFromFile("resources/Font/sansation.ttf")) { return false; }

	if (!aircraftTex.loadFromFile("resources/Textures/aircraft_player.png")) { return false; }
	if (!backgroundTex.loadFromFile("resources/Textures/texture_background.jpg")) { return false; }
	if (!btnTex.loadFromFile("resources/Textures/texture_button.png")) { return false; }
	if (!health.loadFromFile("resources/Textures/heart.png")) { return false; }
	if (!healthBg.loadFromFile("resources/Textures/heart_bg.png")) { return false; }
	
	if (!bgmBuffer.loadFromFile("resources/Audio/music_background.wav")) { return false; }
	if (!thrustBuffer.loadFromFile("resources/Audio/thrust1.wav")) { return false; }
	return true;
}
void Setupbackground(){
	bg.setTexture(backgroundTex);


}

void StartGame() {
	state = GameState::STATE_GAME;
}

void Start() {
	bgm.play();
	bgm.setLoop(true);
}

void LoadLevel() {

}

int main() {

	bool gameStart = false;
	bool loadLevel = false;
	bool pause = false;
	state = GameState::STATE_MENU;

	settings.antialiasingLevel = 8;
	sf::RenderWindow window(sf::VideoMode(winSize.x, winSize.y), "Asteroids", sf::Style::Default, settings);
	if (!LoadResources()) { return EXIT_FAILURE; }

	bg.setTexture(backgroundTex);
	
	startBtn.SetSize(sf::Vector2f(240, 80));
	startBtn.SetTexture(btnTex);
	startBtn.SetClickEvent(&StartGame);
	startBtn.SetPosition(winSize / 2.f);
	startBtn.SetCaption(font, "Start", 40);

	std::vector<Bullet*> bulletPool;
	for (int i = 0; i < 10; ++i) {
		Bullet* bullet = new Bullet();
		bulletPool.push_back(bullet);
	}

	Aircraft player;
	player.SetPosition(winSize / 2.f);
	player.SetTexture(aircraftTex);
	player.SetThrustSound(thrustBuffer);
	player.SetBulletPool(&bulletPool);

	HealthBar healthBar(3);

	healthBar.SetTexture(health);
	healthBar.SetBgTexture(healthBg);
	healthBar.SetSize(60, 20);
	healthBar.SetPosition(1, 1);


	sf::Clock clock;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		float deltaTime = clock.restart().asSeconds();

		window.clear();

		switch (state) {
		case GameState::STATE_MENU: {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);

			startBtn.Update(mousePos);

			window.draw(startBtn);
		} break;
		case GameState::STATE_OPTION: {
			
		}break;
		case GameState::STATE_GAME: {
			if (!gameStart) {
				Start();
				gameStart = true;
				loadLevel = false;
			}
			if (!loadLevel) {
				loadLevel = true;
			}
			if (!pause) {
				player.Update(deltaTime);
			}

			window.draw(bg);

			for (auto bullet : bulletPool) {

				sf::Vector2f position = bullet->getPosition();
				if (position.x < 0 || position.x > winSize.x || position.y <0 || position.y > winSize.y) {
					bullet->enabled = false;
				}
				if (!bullet->enabled) { continue; }
				bullet->Update(deltaTime);
				window.draw(*bullet);
			}

			window.draw(healthBar);
			window.draw(player);
		} break;
		case GameState::STATE_OVER: {

		} break;
		default:
			break;
		}
		window.display();
	}
	return EXIT_SUCCESS;
}