#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#include <iostream>
#include <vector>
#include <memory>

#include "GameObject.h"
#include "GameState.h"
#include "Button.h"
#include "Aircraft.h"
#include "HealthBar.h"
#include "Asteroid.h"
#include "Score.h"

class Time {
public:
	static float deltaTime;

};


/*Window*/
sf::Vector2f winSize(1366, 768);
sf::RenderWindow window(sf::VideoMode(winSize.x, winSize.y), "Asteroids", sf::Style::Default);

/*GameState*/
GameState state;
bool gameStart = false;
bool loadLevel = false;
bool respawn = false;
bool pause = false;

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
sf::SoundBuffer asteroidBuffer;
sf::SoundBuffer bulletBuffer;
sf::SoundBuffer playerExplosionBuffer;

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
sf::Text levelText;
//Button
sf::Vector2f btnSize(240, 80);
std::vector<Button*> menuBtnList;
Button startBtn;
Button exitBtn;
//Health Bar
HealthBar healthBar(3);

/*GameObjects*/


Aircraft* player = new Aircraft();
std::vector<Bullet*> bulletPool;
std::vector<Asteroid*> asteroidPool;
std::vector<GameObject*> objectPool;
std::vector<GameObject*> bucket[4][3];
//std::vector<std::vector<std::vector<GameObject*>>> bucket;
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
	if (!asteroidBuffer.loadFromFile("resources/Audio/explosion_asteroid.wav")) { return false; }
	if (!bulletBuffer.loadFromFile("resources/Audio/weapon_player.wav")) { return false; }
	if (!playerExplosionBuffer.loadFromFile("resources/Audio/explosion_player.wav")) { return false; }

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

void Play() {
	state = GameState::STATE_GAME;
}
void Exit() {
	pause = true;
	if (Confirm(L"Exit?")) {
		window.close();
	}
	else {
		pause = false;
	}
}
void Return2Menu() {
	state = GameState::STATE_MENU;
}

void Init() {


	bg.setTexture(backgroundTex);

	debug.setFont(font);
	debug.setCharacterSize(40);
	debug.setPosition(1, 1);

	startBtn.SetSize(sf::Vector2f(240, 80));
	startBtn.SetTexture(btnTex);
	startBtn.SetClickEvent(&Play);
	startBtn.SetPosition(winSize.x / 2.f, winSize.y /2 );
	startBtn.SetCaption(font, "Start", 40);
	menuBtnList.push_back(&startBtn);

	exitBtn.SetSize(sf::Vector2f(240, 80));
	exitBtn.SetTexture(btnTex);
	exitBtn.SetClickEvent(&Exit);
	exitBtn.SetPosition(winSize.x / 2.f, winSize.y / 2 + 100);
	exitBtn.SetCaption(font, "Exit", 40);
	exitBtn.SetColor(sf::Color::Red);
	menuBtnList.push_back(&exitBtn);


	healthBar.SetTexture(health);
	healthBar.SetBgTexture(healthBg);
	healthBar.SetSize(60, 20);
	healthBar.SetPosition(1, 1);


	ingameScore.setFont(font);
	ingameScore.setCharacterSize(40);
	ingameScore.setPosition(10, 80);


	endGameScore.setFont(font);
	endGameScore.setCharacterSize(80);
	endGameScore.setPosition(10, 80);

	levelText.setFont(font);
	levelText.setCharacterSize(80);
	levelText.setPosition(1000, 80);

	for (int i = 0; i < 200; ++i) {
		Bullet* bullet = new Bullet();
		bullet->SetTexture(bulletTex);
		bullet->boundary = winSize;
		bulletPool.push_back(bullet);
		objectPool.push_back(bullet);
	}

	player->SetTexture(aircraftTex);
	player->SetThrustSound(thrustBuffer);
	player->SetBulletPool(&bulletPool);
	player->SetBulletSound(bulletBuffer);
	player->SetExplosionSound(playerExplosionBuffer);
	objectPool.push_back(player);

	for (int i = 0; i < 100; i++) {
		Asteroid* a = new Asteroid();
		a->SetTexture(asteroidTex);
		a->SetPosition(sf::Vector2f(rand() % 1366, (rand() % 768)));
		a->SetDirection(rand() % 10, rand() % 10);
		a->speed = rand() % 20 + 50;
		a->boundary = winSize;
		a->rotateSpeed = (rand() % 10 + 30);
		a->container = &asteroidPool;
		a->enable = false;
		a->playerScore = &score;
		a->SetBuffer(asteroidBuffer);
		asteroidPool.push_back(a);
		objectPool.push_back(a);
	}

}

void Start() {
	bgm.play();
	bgm.setLoop(true);
}

void LoadLevel(int index) {
	for (int i = 0; i < 3 + index; ++i) {
		asteroidPool[i]->SetLife(3);
		asteroidPool[i]->enable = true;
	}
}

void SpawnPlayer() {
	player->SetPosition(winSize / 2.f);
}

int main() {
	int currentLevel = 0;
	state = GameState::STATE_MENU;
	
	if (!LoadResources()) { return EXIT_FAILURE; }
	//window.setFramerateLimit(60);

	Init();

	sf::Clock clock;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			if (event.type == sf::Event::KeyPressed) {
				switch (state)
				{
				case GameState::STATE_MENU: break;
				case GameState::STATE_GAME: {
					if (event.key.code == sf::Keyboard::Escape) {
						pause = true;
						if (Confirm(L"Quit Game?")) {
							Return2Menu();
						}
						pause = false;
					}
				} break;
				case GameState::STATE_OVER: {
					Return2Menu();
				} break;
				default: break;
				}
			}
		}

		float deltaTime = clock.restart().asSeconds();
		debug.setString(std::to_string((int)(1 / deltaTime))); 

		window.clear();

		window.draw(bg);
		switch (state) {
		case GameState::STATE_MENU: {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			for (auto button : menuBtnList) {
				button->Update(mousePos);
				window.draw(*button);
			}

		} break;
		case GameState::STATE_GAME: {

			/*GameSetup*/
			if (!gameStart) {
				Start();
				gameStart = true;
				loadLevel = false;
			}
			if (!loadLevel) {
				LoadLevel(currentLevel);
				++currentLevel;
				levelText.setString("Level:" + std::to_string(currentLevel));
				loadLevel = true;
				respawn = true;

			}

			if (respawn) {
				player->SetPosition(winSize / 2.f);
				player->Enable();
				respawn = false;
			}

			for (int i = 0; i < 4; i++) {
				for (int j = 0; j < 3; j++) {
					bucket[i][j].clear();
				}
			}

			/*Update*/
			if (!pause) {

				sf::Vector2f bucketCellSize((winSize.x + 120) / 4.f, (winSize.y  + 120) / 3.f);
				//Update object then put them in bucket
				for (const auto& object : objectPool) {
					if (object->enable) {
						object->Update(deltaTime);

						//Put objects to corresponding bucket
						int xIndex = object->position.x / bucketCellSize.x;
						int yIndex = object->position.y / bucketCellSize.y;

						bool outLeft = object->position.x - object->radius - xIndex * bucketCellSize.x < 0;
						bool outRight = object->position.x + object->radius - (xIndex + 1) * bucketCellSize.x > 0;

						bool outTop = object->position.y - object->radius - yIndex * bucketCellSize.y < 0;
						bool outDown = object->position.y + object->radius - (yIndex + 1) * bucketCellSize.y > 0;

						bucket[xIndex][yIndex].push_back(object);

						//Left bucket
						if (outLeft && xIndex > 0) {
							bucket[xIndex - 1][yIndex].push_back(object);
						}
						//Right bucket
						if (outRight && xIndex < 4) {
							bucket[xIndex + 1][yIndex].push_back(object);
						}
						//Top bucket
						if (outTop && yIndex > 0) {
							bucket[xIndex][yIndex - 1].push_back(object);
						}
						//Down bucket
						if (outDown && yIndex < 3) {
							bucket[xIndex][yIndex + 1].push_back(object);
						}

						//Top left
						if (outLeft && xIndex > 0 && outTop && yIndex > 0) {
							bucket[xIndex - 1][yIndex - 1].push_back(object);
						}
						//Top Right
						if (outRight && xIndex < 4 && outTop && yIndex > 0) {
							bucket[xIndex + 1][yIndex - 1].push_back(object);
						}

						//Down left
						if (outLeft && xIndex > 0 && outDown && yIndex < 3) {
							bucket[xIndex - 1][yIndex + 1].push_back(object);
						}
						//Down Right
						if (outRight && xIndex < 4 && outDown && yIndex < 3) {
							bucket[xIndex + 1][yIndex + 1].push_back(object);
						}


					}
				}

				/*Bucket Grid*/
				for (int i = 0; i < 4; ++i) {
					for (int j = 0; j < 3; ++j) {
						for (int a = 0; a < bucket[i][j].size(); ++a) {
							for (int b = a + 1; b < bucket[i][j].size(); ++b) {
								sf::Vector2f diff = bucket[i][j][a]->position - bucket[i][j][b]->position;
								float r2 = pow((bucket[i][j][a]->radius + bucket[i][j][b]->radius), 2);
								if (pow(diff.x, 2) + pow(diff.y, 2) <= r2) {
									bucket[i][j][a]->Collide(*bucket[i][j][b]);
									bucket[i][j][b]->Collide(*bucket[i][j][a]);
								}
							}
						}
					}
				}

			}

			if (player->enable == false) {
				healthBar.DecreaseHealth();
				respawn = true;
			}
			

			/*Render*/
			for (const auto& object : objectPool) {
				if (object->enable) {
					window.draw(*object);
				}
			}

			window.draw(healthBar);
			window.draw(levelText);
			ingameScore.setString(std::to_string(score));
			window.draw(ingameScore);

			/*GameOver*/
			if (healthBar.isEmpty()) {
				state = GameState::STATE_OVER;
			}
			loadLevel = false;
			for (auto asteroid : asteroidPool) {
				if (asteroid->enable) {
					loadLevel = true;
				}
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