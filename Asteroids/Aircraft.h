#pragma once
#include <SFML/Graphics.hpp>
class Aircraft : public sf::Sprite {
private:
	sf::Vector2f size;

	float headingAngle;
	float speed;

public:
	Aircraft();
	~Aircraft();
	void SetSize(sf::Vector2f size);
	void SetSize(float x, float y);
	sf::Vector2f GetSize();

	void SetDirection(float angle);
	sf::Vector2f GetDirection();

	void Move(float dt);
};
