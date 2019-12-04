#pragma once
#include "GameObject.h"
#include <SFML/Audio.hpp>
class Bullet : public GameObject{
public:
	float headingAngle;

	sf::Vector2f boundary;

	Bullet();

	~Bullet();

	/*Getters and Setters*/
	void SetHeading(float angle);
	float GetHeading();

	void SetSpeed(float speed);
	float GetSpeed();

	void SetPosition(sf::Vector2f position);
	void SetPosition(float x, float y);

	void Move(float dt);
	
	void Disable();

	void Update(float dt);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void Collide(GameObject& other);
};