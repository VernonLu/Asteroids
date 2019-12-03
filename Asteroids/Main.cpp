#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#include <iostream>
#include <vector>

#include "GameObject.h"
#include "GameState.h"
#include "Button.h"
#include "Aircraft.h"
#include "HealthBar.h"
#include "Asteroid.h"


sf::Vector2f winSize(1366, 768);
sf::ContextSettings settings;
GameState state;

sf::Vector2f btnSize(240, 80);

sf::Font font;

sf::Sprite bg;

/*Texture*/
sf::Texture aircraftTex;
sf::Texture backgroundTex;
sf::Texture btnTex;
sf::Texture health;
sf::Texture healthBg;
sf::Texture bulletTex;
sf::Texture asteroidTex;

/*Sound*/
sf::SoundBuffer bgmBuffer;
sf::Sound bgm(bgmBuffer);

sf::SoundBuffer thrustBuffer;

/*Text*/
sf::Text debug;

/*Button*/
std::vector<Button*> menuBtnList;
Button startBtn;


bool LoadResources() {
	//Load font
	if (!font.loadFromFile("resources/Font/sansation.ttf")) { return false; }

	//Load texture
	if (!aircraftTex.loadFromFile("resources/Textures/aircraft_player.png")) { return false; }
	if (!backgroundTex.loadFromFile("resources/Textures/texture_background.jpg")) { return false; }
	if (!btnTex.loadFromFile("resources/Textures/texture_button.png")) { return false; }
	if (!health.loadFromFile("resources/Textures/heart.png")) { return false; }
	if (!healthBg.loadFromFile("resources/Textures/heart_bg.png")) { return false; }
	if (!bulletTex.loadFromFile("resources/Textures/bullet.png")) { return false; }
	if (!asteroidTex.loadFromFile("resources/Textures/asteroid.png")) { return false; }

	//Load sound
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

	std::vector<GameObject*> bucket;


	bool gameStart = false;
	bool loadLevel = false;
	bool pause = false;
	state = GameState::STATE_MENU;

	debug.setFont(font);
	debug.setCharacterSize(40);
	debug.setPosition(1, 1);

	settings.antialiasingLevel = 8;
	
	sf::RenderWindow window(sf::VideoMode(winSize.x, winSize.y), "Asteroids", sf::Style::Default, settings);
	
	if (!LoadResources()) { return EXIT_FAILURE; }

	std::vector<Asteroid*> largeAsteroid;
	for (int i = 0; i < 10; ++i) {
		Asteroid* a = new Asteroid();
		a->SetTexture(asteroidTex);
		a->SetPosition(sf::Vector2f(rand() % 1366, (rand() % 768)));
		a->SetDirection(773 - a->position.x + (rand() % 10 - 5)* 10, 384 - a->position.y + (rand() % 10 - 5) * 10);
		a->speed = rand() % 20 + 100;
		a->boundary = winSize;
		a->rotateSpeed = (rand() % 10 + 30);
		largeAsteroid.push_back(a);
	}

	bg.setTexture(backgroundTex);
	
	startBtn.SetSize(sf::Vector2f(240, 80));
	startBtn.SetTexture(btnTex);
	startBtn.SetClickEvent(&StartGame);
	startBtn.SetPosition(winSize / 2.f);
	startBtn.SetCaption(font, "Start", 40);

	std::vector<Bullet*> bulletPool;
	for (int i = 0; i < 5000; ++i) {
		Bullet* bullet = new Bullet();
		bullet->SetTexture(bulletTex);
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
		debug.setString(std::to_string((int)(1 / deltaTime))); 

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

			for (auto asteroid : largeAsteroid) {
				asteroid->Update(deltaTime);
				window.draw(*asteroid);
			}
			for (int i = 0; i < largeAsteroid.size(); ++i) {
				for (int j = i + 1; j < largeAsteroid.size(); ++j) {
					sf::Vector2f diff = largeAsteroid[i]->position - largeAsteroid[j]->position;
					float r2 = pow((largeAsteroid[i]->radius + largeAsteroid[j]->radius), 2);
					if (pow(diff.x, 2) + pow(diff.y, 2) <= r2) {
						largeAsteroid[i]->Collide(*largeAsteroid[j]);
						largeAsteroid[j]->Collide(*largeAsteroid[i]);
					}
				}
			}

			for (auto bullet : bulletPool) {

				sf::Vector2f position = bullet->position;
				if (position.x < 0 || position.x > winSize.x || position.y <0 || position.y > winSize.y) {
					bullet->enable = false;
				}
				if (!bullet->enable) { continue; }
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
		window.draw(debug);
		window.display();
	}
	return EXIT_SUCCESS;
}