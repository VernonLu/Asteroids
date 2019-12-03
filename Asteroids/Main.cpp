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
#include "Score.h"


sf::Vector2f winSize(1366, 768);
sf::ContextSettings settings;
GameState state;

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

/*UI*/
//Font
sf::Font font;
//Background
sf::Sprite bg;
//Text
sf::Text debug;
int score;
sf::Text ingameScore;
sf::Text endGameScore;
//Button
sf::Vector2f btnSize(240, 80);
std::vector<Button*> menuBtnList;
Button startBtn;
//Health Bar
HealthBar healthBar(3);

/*GameObjects*/

std::vector<GameObject*> bucket;
Aircraft player;
std::vector<Bullet*> bulletPool;
std::vector<Asteroid*> asteroidPool;

bool LoadResources() {
	//Load font
	if (!font.loadFromFile("resources/Font/sansation.ttf")) { return false; }

	//Load texture
	if (!aircraftTex.loadFromFile("resources/Textures/aircraft_player.png")) { return false; }
	if (!backgroundTex.loadFromFile("resources/Textures/texture_background.jpg")) { return false; }
	if (!btnTex.loadFromFile("resources/Textures/button.png")) { return false; }
	if (!health.loadFromFile("resources/Textures/heart.png")) { return false; }
	if (!healthBg.loadFromFile("resources/Textures/heart_bg.png")) { return false; }
	if (!bulletTex.loadFromFile("resources/Textures/bullet.png")) { return false; }
	if (!asteroidTex.loadFromFile("resources/Textures/asteroid.png")) { return false; }

	//Load sound
	if (!bgmBuffer.loadFromFile("resources/Audio/music_background.wav")) { return false; }
	if (!thrustBuffer.loadFromFile("resources/Audio/thrust1.wav")) { return false; }

	return true;
}


/*Confirm Window*/
bool Confirm(LPCWSTR str) {
	return (MessageBox(
		NULL,
		str,
		(LPCWSTR)L"Alert",//Caption
		MB_YESNO | MB_ICONINFORMATION
	) == 6);
}

void StartGame() {
	state = GameState::STATE_GAME;
}

void Init() {

	bg.setTexture(backgroundTex);

	debug.setFont(font);
	debug.setCharacterSize(40);
	debug.setPosition(1, 1);

	startBtn.SetSize(sf::Vector2f(240, 80));
	startBtn.SetTexture(btnTex);
	startBtn.SetClickEvent(&StartGame);
	startBtn.SetPosition(winSize / 2.f);
	startBtn.SetCaption(font, "Start", 40);


	healthBar.SetTexture(health);
	healthBar.SetBgTexture(healthBg);
	healthBar.SetSize(60, 20);
	healthBar.SetPosition(1, 1);


	ingameScore.setFont(font);
	ingameScore.setCharacterSize(40);
	ingameScore.setPosition(10, 80);


	player.SetTexture(aircraftTex);
	player.SetThrustSound(thrustBuffer);
	player.SetBulletPool(&bulletPool);

}

void Start() {
	bgm.play();
	bgm.setLoop(true);
}

void LoadLevel(int index) {
	for (int i = 0; i < 10; ++i) {
		Asteroid* a = new Asteroid();
		a->SetTexture(asteroidTex);
		a->SetPosition(sf::Vector2f(rand() % 1366, (rand() % 768)));
		a->SetDirection(rand() % 10, rand() % 10);
		a->speed = rand() % 20 + 50;
		a->boundary = winSize;
		a->rotateSpeed = (rand() % 10 + 30);
		asteroidPool.push_back(a);
	}
}

void SpawnPlayer() {

	for (int i = 0; i < 5000; ++i) {
		Bullet* bullet = new Bullet();
		bullet->SetTexture(bulletTex);
		bulletPool.push_back(bullet);
	}

	player.SetPosition(winSize / 2.f);
}

int main() {
	bool gameStart = false;
	bool loadLevel = false;
	bool respawn = false;
	bool pause = false;

	state = GameState::STATE_MENU;

	settings.antialiasingLevel = 8;
	
	sf::RenderWindow window(sf::VideoMode(winSize.x, winSize.y), "Asteroids", sf::Style::Default, settings);
	
	if (!LoadResources()) { return EXIT_FAILURE; }

	Init();

	sf::Clock clock;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				pause = true;
				if (Confirm(L"Exit")) {
					window.close();
					break;
				}
				else {
					pause = false;
					clock.restart();
				}
			}
		}

		float deltaTime = clock.restart().asSeconds();
		//debug.setString(std::to_string((int)(1 / deltaTime))); 

		window.clear();

		window.draw(bg);
		switch (state) {
		case GameState::STATE_MENU: {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);

			startBtn.Update(mousePos);

			window.draw(startBtn);
		} break;
		case GameState::STATE_GAME: {

			/*GameSetup*/
			if (!gameStart) {
				Start();
				gameStart = true;
				loadLevel = false;
			}
			if (!loadLevel) {
				loadLevel = true;
			}

			/*Update*/
			if (!pause) {
				player.Update(deltaTime);
				for (auto asteroid : asteroidPool) {
					asteroid->Update(deltaTime);
				}

				for (auto bullet : bulletPool) {

					sf::Vector2f position = bullet->position;
					if (position.x < 0 || position.x > winSize.x || position.y <0 || position.y > winSize.y) {
						bullet->enable = false;
					}
					if (!bullet->enable) { continue; }
					bullet->Update(deltaTime);
				}
				/*Collision Detection*/
				for (int i = 0; i < asteroidPool.size(); ++i) {
					for (int j = i + 1; j < asteroidPool.size(); ++j) {
						sf::Vector2f diff = asteroidPool[i]->position - asteroidPool[j]->position;
						float r2 = pow((asteroidPool[i]->radius + asteroidPool[j]->radius), 2);
						if (pow(diff.x, 2) + pow(diff.y, 2) <= r2) {
							asteroidPool[i]->Collide(*asteroidPool[j]);
							asteroidPool[j]->Collide(*asteroidPool[i]);
						}
					}
				}

				if (player.enable == false) {
					healthBar.DecreaseHealth();
					respawn = true;
				}
			}

			

			/*Render*/

			for (auto asteroid : asteroidPool) {
				if(asteroid->enable)
					window.draw(*asteroid);
			}
			for (auto bullet : bulletPool) {
				if (bullet->enable)
					window.draw(*bullet);
			}
			window.draw(player);

			window.draw(healthBar);

			ingameScore.setString(std::to_string(score));
			window.draw(ingameScore);

			/*GameOver*/
			if (healthBar.isEmpty()) {
				state = GameState::STATE_OVER;
			}
		} break;
		case GameState::STATE_OVER: {

			endGameScore.setString(std::to_string(score));
			window.draw(endGameScore);
		} break;
		default:
			break;
		}
		window.draw(debug);
		window.display();
	}
	return EXIT_SUCCESS;
}