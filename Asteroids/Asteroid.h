#pragma once
#include "GameObject.h"

class Asteroid : public GameObject {
public:

	int life;

	sf::Vector2f boundary;

	float rotateSpeed;

	std::vector<Asteroid*>* container;

	int* playerScore;

	sf::Sound sound;

	Asteroid(int life = 3);
	~Asteroid();

	void SetLife(int value);

	void SetPosition(sf::Vector2f position);

	void SetDirection(float x, float y);

	void SetBuffer(sf::SoundBuffer& buffer);

	void Move(float dt);

	void Rotate(float dt);

	void SetRadius(float value);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void Update(float dt);

	void Collide(GameObject& other);

	void Destroy();
};