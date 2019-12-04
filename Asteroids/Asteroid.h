#pragma once
#include "GameObject.h"

class Asteroid : public GameObject {
public:

	int life;

	sf::Vector2f boundary;

	float rotateSpeed;

	std::vector<Asteroid*>* container;

	Asteroid();
	~Asteroid();

	void SetPosition(sf::Vector2f position);

	void SetDirection(float x, float y);

	void Move(float dt);

	void Rotate(float dt);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void Update(float dt);

	void Collide(GameObject& other);

	void Destroy();
};